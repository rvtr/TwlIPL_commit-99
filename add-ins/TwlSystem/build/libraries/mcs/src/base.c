/*---------------------------------------------------------------------------*
  Project:  NITRO-System - libraries - mcs
  File:     base.c

  Copyright 2004-2008 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 635 $
 *---------------------------------------------------------------------------*/

#if ! defined(NNS_FINALROM)

#include <nitro.h>
#include <nnsys/misc.h>
#include <nnsys/mcs/baseCommon.h>
#include <nnsys/mcs/base.h>
#include <nnsys/mcs/ringBuffer.h>
#include <nnsys/mcs/config.h>
#include <isdbglib.h>
#include <istdbglib.h>
#include "baseCommoni.h"
#include "basei.h"


/* ========================================================================
    �萔
   ======================================================================== */

static const int SEND_RETRY_MAX = 10;
static const int UIC_WAIT_TIMEOUT_FRAME = 60 * 2;


/* ========================================================================
    �^��`
   ======================================================================== */

typedef struct DefRecvCBInfo DefRecvCBInfo;
struct DefRecvCBInfo
{
    NNSMcsRecvCBInfo    cbInfo;
    NNSMcsRingBuffer    ringBuf;
};

typedef struct NNSiMcsEnsWork NNSiMcsEnsWork;
struct NNSiMcsEnsWork
{
    NNSMcsRingBuffer    rdRb;
    NNSMcsRingBuffer    wrRb;
    NNSiMcsEnsMsgBuf    msgBuf;
};


/* ========================================================================
    static�ϐ�
   ======================================================================== */

static NNSiMcsWork*     spMcsWork   = NULL;     // ����������Ă���� NULL �ȊO�ɂȂ�

static NNSMcsDeviceCaps sDeviceCaps =
                        {
                            NITRODEVID_NULL,    // �f�o�C�X����ID
                            0x00000000,         // ���\�[�X���ʏ��̃t���O
                        };


/* ========================================================================
    static�֐�
   ======================================================================== */

static NNS_MCS_INLINE
BOOL
IsInitialized()
{
    return spMcsWork != NULL;
}

static NNS_MCS_INLINE
uint32_t
RoundUp(
    uint32_t    value,
    uint32_t    alignment
)
{
    return (value + alignment -1) & ~(alignment -1);
}

static NNS_MCS_INLINE
uint32_t
RoundDown(
    uint32_t    value,
    uint32_t    alignment
)
{
    return value & ~(alignment -1);
}

static NNS_MCS_INLINE
u32
min_u32(
    u32     a,
    u32     b
)
{
    return a < b ? a: b;
}

static NNS_MCS_INLINE void
Lock()
{
    if (OS_IsThreadAvailable())
    {
        OS_LockMutex(&spMcsWork->mutex);
    }
}

static NNS_MCS_INLINE void
Unlock()
{
    if (OS_IsThreadAvailable())
    {
        OS_UnlockMutex(&spMcsWork->mutex);
    }
}

/*
    �`�����l�����w�肵�āANNSMcsRecvCBInfo�ւ̃|�C���^�𓾂�
*/
static NNSMcsRecvCBInfo*
GetRecvCBInfo(
    NNSFndList* pList,
    uint32_t    channel
)
{
    NNSMcsRecvCBInfo* pInfo = NULL;

    while (NULL != (pInfo = NNS_FndGetNextListObject(pList, pInfo)))
    {
        if (pInfo->channel == channel)
        {
            return pInfo;
        }
    }

    return NULL;
}

static void
CallbackRecv(
    u32         userData,
    u32         channel,
    const void* pRecv,
    uint32_t    recvSize
)
{
    const NNSiMcsMsg *const pMsg = (NNSiMcsMsg*)pRecv;
    const u32 dataSize = recvSize - NNSi_MCS_MSG_HEAD_SIZE;

    // TWL�p�ʐM���C�u�����ł́A��M�R�[���o�b�N�֐����ʃX���b�h�ŌĂяo�����
    // �̂ŁA�r��������s���܂��B
    Lock();

    if ( recvSize < NNSi_MCS_MSG_HEAD_SIZE
      || NNSi_MCS_MSG_HEAD_VERSION != pMsg->head.version
    )
    {
        // OS_Printf("CallbackRecv() protocol error.\n");
        spMcsWork->bProtocolError = TRUE;
    }
    else
    {
        if (NNSi_MCS_SYSMSG_CHANNEL == channel)
        {
            u32 bConnect;

            if (dataSize == sizeof(bConnect))
            {
                bConnect = *(u32*)pMsg->data;
                spMcsWork->bHostDataRecived = (u8)bConnect;
                // OS_Printf("CallbackRecv() NNSi_MCS_SYSMSG_CHANNEL connect %d\n", bConnect);
            }
            else
            {
                // OS_Printf("CallbackRecv() NNSi_MCS_SYSMSG_CHANNEL data size error %d\n", dataSize);
            }
        }
        else
        {
            NNSFndList *const pList = (NNSFndList*)userData;
            NNSMcsRecvCBInfo *const pInfo = GetRecvCBInfo(pList, channel);

            // OS_Printf("CallbackRecv() [%04X, %p, %05d %08X, %p]\n", channel, pRecv, recvSize, userData, pInfo);

            if (pInfo)
            {
                (*pInfo->cbFunc)(pMsg->data, dataSize, pInfo->userData, pMsg->head.offset, pMsg->head.totalLen);
            }
        }
    }

    Unlock();
}

static void
CallbackRecvDummy(
    uintptr_t   /* userData */,
    uint32_t    /* channel */,
    const void* /* pRecv */,
    uint32_t    /* recvSize */
)
{
    // �������Ȃ�
}

static void
DataRecvCallback(
    const void* pData,
    u32         dataSize,
    u32         userData,
    u32         offset,
    u32         totalSize
)
{
    DefRecvCBInfo* cbInfo = (DefRecvCBInfo*)userData;

    if (NNS_McsGetRingBufferWritableBytes(cbInfo->ringBuf) < offset + dataSize)
    {
        // �G���[ - �o�b�t�@���������
        NNS_WARNING(FALSE, "NNS mcs error : buffer is not enough. writable %d, data size %d, offset %d, total size %d\n",
            NNS_McsGetRingBufferWritableBytes(cbInfo->ringBuf),
            dataSize,
            offset,
            totalSize);
        return;
    }

    {
        BOOL ret = NNS_McsWriteRingBufferEx(
            cbInfo->ringBuf,
            pData,
            offset,
            dataSize,
            totalSize);
        NNS_ASSERT(ret);
    }
}

static NNS_MCS_INLINE NNSiMcsEnsWork*
GetEnsWorkPtr()
{
    return (NNSiMcsEnsWork*)NNSi_MCS_ENS_WRITE_RB_END;
}

static void
SetMaskResource(u32 maskResource)
{
    const BOOL preIRQ = OS_DisableIrq();
    sDeviceCaps.maskResource = maskResource;
    (void)OS_RestoreIrq(preIRQ);
}

static void
WaitSendData(void)
{
    NNS_McsPollingIdle();   // PC�����������ݑ҂��Ńu���b�N���Ă��܂�Ȃ��悤�ɂ��Ă���

    NNSi_McsSleep(8);
}

static void
WaitDeviceEnable(void)
{
    NNS_McsPollingIdle();

    NNSi_McsSleep(16);
}

int         _isdbusmgr_isresourceavailable(int /*typeResource*/);

__declspec ( weak )
int
_isdbusmgr_isresourceavailable(int /*typeResource*/)
{
    return FALSE;
}

static BOOL
IsDebuggerPresent()
{
    static const int    ISDRESOURCE_SW_DEBUGGER    =   0x00200;

    return _isdbusmgr_isresourceavailable(ISDRESOURCE_SW_DEBUGGER);
}

static BOOL
OpenEnsata(NNSMcsDeviceCaps* pCaps)
{
    const NNSMcsRingBuffer rdRb = (NNSMcsRingBuffer)NNSi_MCS_ENS_READ_RB_START;
    const NNSMcsRingBuffer wrRb = (NNSMcsRingBuffer)NNSi_MCS_ENS_WRITE_RB_START;

    if (! NNS_McsCheckRingBuffer(rdRb) || ! NNS_McsCheckRingBuffer(wrRb))
    {
        return FALSE;
    }

    {
        NNSiMcsEnsWork* pWork = GetEnsWorkPtr();
        pWork->rdRb = rdRb;
        pWork->wrRb = wrRb;
    }

    pCaps->deviceID     = 0;
    pCaps->maskResource = NITROMASK_RESOURCE_POLL;

    return TRUE;
}

static BOOL
OpenHwNitro(NNSMcsDeviceCaps* pCaps)
{
    // �f�o�C�X�̗D��x PRIority
    enum
    {
        DEV_PRI_NONE,               // �f�o�C�X�Ȃ�
        DEV_PRI_UNKNOWN,            // ���m�̃f�o�C�X
        DEV_PRI_NITRODBG,           // IS-NITRO-DEBUGGER
        DEV_PRI_NITROUIC,           // IS-NITRO-UIC
        DEV_PRI_NITROUSB,           // IS-NITRO-EMULATOR

        DEV_PRI_MAX
    };

    int devPri = DEV_PRI_NONE;
    int devID = 0;
    const int devNum = NNS_McsGetMaxCaps();
    int findDevID = 0;
    const NITRODEVCAPS* pNITROCaps;
    // OS_Printf("on DEBBUGER ? %s\n", IsDebuggerPresent() ? "yes": "no");

    for (findDevID = 0; findDevID < devNum; ++findDevID)
    {
        int findDevPri = DEV_PRI_NONE;
        pNITROCaps = NITROToolAPIGetDeviceCaps(findDevID);
        switch (pNITROCaps->m_nDeviceID)
        {
        case NITRODEVID_NITEMULATOR:    // IS-NITRO-EMULATOR
            if (IsDebuggerPresent())
            {
                findDevPri = DEV_PRI_NITRODBG;
            }
            else    // IS-NITRO-DEBUGGER �\�t�g�E�F�A����N�����Ă��Ȃ��Ƃ�
            {
                findDevPri = DEV_PRI_NITROUSB;
            }
            break;
        case NITRODEVID_NITUIC:         // IS-NITRO-UIC CARTRIDGE
            findDevPri = DEV_PRI_NITROUIC;
            break;
        default:
            findDevPri = DEV_PRI_UNKNOWN;
        }

        if (devPri < findDevPri)
        {
            devPri = findDevPri;
            devID  = findDevID;
        }
    }

    if (devPri == DEV_PRI_NONE || devPri == DEV_PRI_UNKNOWN)
    {
        OS_Warning("no device.\n");     // �ڑ��\�ȃf�o�C�X��������܂���B
        return FALSE;
    }

    pNITROCaps = NITROToolAPIGetDeviceCaps(devID);
    if (! NITROToolAPIOpen(pNITROCaps))
    {
        return FALSE;   // �f�o�C�X�̃I�[�v��&�������Ɏ��s���܂���
    }

    pCaps->deviceID     = pNITROCaps->m_nDeviceID;
    pCaps->maskResource = pNITROCaps->m_dwMaskResource;
    spMcsWork->bLengthEnable = FALSE;

    {
        // �R�[���o�b�N�֐��̓o�^�iWidows���̃A�v���P�[�V��������f�[�^�����M�����΁A���̊֐����Ă΂��j
        BOOL bSuccess = NITROToolAPISetReceiveStreamCallBackFunction(CallbackRecv, (u32)&spMcsWork->recvCBInfoList);
        NNS_ASSERT(bSuccess);
    }

    return TRUE;
}

static BOOL
OpenHwTwl(NNSMcsDeviceCaps* pCaps)
{
    u32 nDevMask;

    // �R�[���o�b�N�o�^
    ISTDSIOSetRecvCallback( (ISTDSIORecvCbFunc)CallbackRecv, (void*)&spMcsWork->recvCBInfoList );

    //
    nDevMask = ISTDHIOGetDevMask();
    if (nDevMask == 0 || !ISTDHIOOpen(nDevMask))
    {
        OS_Printf(" ISHIO: device open failure. - DevMask %08X\n", nDevMask);
        return FALSE;
    }

    pCaps->deviceID     = 0;
    pCaps->maskResource = NITROMASK_RESOURCE_POLL;

    return TRUE;

}

static NNS_MCS_INLINE BOOL
CloseEnsata()
{
    NNSiMcsEnsWork* pWork = GetEnsWorkPtr();
    pWork->rdRb = 0;
    pWork->wrRb = 0;

    return TRUE;
}

/* ========================================================================
    �O���֐�(���J)
   ======================================================================== */

/*---------------------------------------------------------------------------*
  Name:         NNS_McsInit

  Description:  �f�o�C�X�ƒʐM���邽�߂̏������֐��ł��B
                NNS_Mcs�֐����g�p����Ƃ��́A
                �g�p����O�ɕK�����̊֐����Ăяo���Ă����K�v������܂��B

  Arguments:    workMem:  MCS���g�p���郏�[�N�p�������B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------
static void Init_TWL()
{
    ISTDHIOInit();
}

//---------------------------------------------------------
static void Init_Ensata()
{
    // �������Ȃ�
}

//---------------------------------------------------------
static void Init_NITRO()
{
    NITROToolAPIInit();
}

//---------------------------------------------------------
static void Init_InVariousDevice()
{
    if ( OS_IsRunOnTwl() )
    {
#ifdef SDK_TWL
        Init_TWL();
#endif
    }
    else
    {
#ifndef SDK_TWLLTD
        if (OS_IsRunOnEmulator())
            { Init_Ensata(); }
        else
            { Init_NITRO(); }
#endif
    }
}

//---------------------------------------------------------
void
NNS_McsInit(void* workMem)
{
    if (IsInitialized())
    {
        return;
    }

    NNS_NULL_ASSERT(workMem);

    Init_InVariousDevice();

    spMcsWork = (NNSiMcsWork*)workMem;

    spMcsWork->bProtocolError = FALSE;
    spMcsWork->bLengthEnable = FALSE;
    spMcsWork->bHostDataRecived = FALSE;
    OS_InitMutex(&spMcsWork->mutex);
    NNS_FND_INIT_LIST(&spMcsWork->recvCBInfoList, NNSMcsRecvCBInfo, link);
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsGetMaxCaps

  Description:  ���݃^�[�Q�b�g�ɐڑ�����Ă���ʐM�f�o�C�X�̑������擾���܂��B

  Arguments:    �Ȃ��B

  Returns:      ���݃^�[�Q�b�g�ɐڑ�����Ă���ʐM�f�o�C�X�̑�����Ԃ��܂��B
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------
static int GetMaxCaps_TWL()
{
    return 1;
}

//---------------------------------------------------------
static int GetMaxCaps_Ensata()
{
    return 1;
}

//---------------------------------------------------------
static int GetMaxCaps_NITRO()
{
    return NITROToolAPIGetMaxCaps();
}

//---------------------------------------------------------
static int GetMaxCaps_InVariousDevice()
{
    if ( OS_IsRunOnTwl() )
    {
#ifdef SDK_TWL
        return GetMaxCaps_TWL();
#endif
    }
    else
    {
#ifndef SDK_TWLLTD
        if (OS_IsRunOnEmulator())
        { return GetMaxCaps_Ensata(); }
        else
        { return GetMaxCaps_NITRO(); }
#endif
    }
    return 0;
}

//---------------------------------------------------------
int
NNS_McsGetMaxCaps()
{
    int num;

    NNS_ASSERT(IsInitialized());
    Lock();

    num = GetMaxCaps_InVariousDevice();

    Unlock();
    return num;
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsOpen

  Description:  �f�o�C�X���I�[�v�����A�I�[�v�������f�o�C�X�̏��������Ŏw�肵��
                �ϐ��֊i�[���܂��B
                �ڑ�����Ă���f�o�C�X���������݂���Ƃ��́A
                �ȉ��̏��Ō��������f�o�C�X���I�[�v�����܂��B
                  1. IS-NITRO-UIC
                  2. IS-NITRO-EMULATOR
                  4. ���m�̃f�o�C�X

  Arguments:    pCaps:  �ʐM�f�o�C�X�̏����擾���邽�߂̍\���̂ւ̃|�C���^�B

  Returns:      �I�[�v���ɐ��������ꍇ�ATRUE��Ԃ��܂��B
                ���s�����ꍇ�AFALSE��Ԃ��܂��B
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------
static BOOL Open_TWL(NNSMcsDeviceCaps* pCaps)
{
    return OpenHwTwl(pCaps);
}

//---------------------------------------------------------
static BOOL Open_Ensata(NNSMcsDeviceCaps* pCaps)
{
    return OpenEnsata(pCaps);
}

//---------------------------------------------------------
static BOOL Open_NITRO(NNSMcsDeviceCaps* pCaps)
{
    return OpenHwNitro(pCaps);
}

//---------------------------------------------------------
static BOOL Open_InVariousDevice(NNSMcsDeviceCaps* pCaps)
{
    if ( OS_IsRunOnTwl() )
    {
#ifdef SDK_TWL
        return Open_TWL(pCaps);
#endif
    }
    else
    {
#ifndef SDK_TWLLTD
        if (OS_IsRunOnEmulator())
        { return Open_Ensata(pCaps); }
        else
        { return Open_NITRO(pCaps); }
#endif
    }
    return FALSE;
}

//---------------------------------------------------------
BOOL
NNS_McsOpen(NNSMcsDeviceCaps* pCaps)
{
    BOOL bSuccess;

    NNS_ASSERT(IsInitialized());
    Lock();

    bSuccess = Open_InVariousDevice(pCaps);

    if (bSuccess)
    {
        sDeviceCaps.deviceID = pCaps->deviceID;
        SetMaskResource(pCaps->maskResource);

        spMcsWork->bHostDataRecived = FALSE;
    }

    Unlock();
    return bSuccess;
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsClose

  Description:  �I�[�v�����Ă���f�o�C�X���N���[�Y���܂��B

  Arguments:    �Ȃ��B

  Returns:      �N���[�Y�ɐ��������ꍇ�ATRUE��Ԃ��܂��B
                ���s�����ꍇ�AFALSE��Ԃ��܂��B
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------
static BOOL Close_TWL()
{
    return ISTDHIOClose();
}

//---------------------------------------------------------
static BOOL Close_Ensata()
{
    return CloseEnsata();
}

//---------------------------------------------------------
static BOOL Close_NITRO()
{
    return NITROToolAPIClose();
}

//---------------------------------------------------------
static BOOL Close_InVariousDevice()
{
    if ( OS_IsRunOnTwl() )
    {
#ifdef SDK_TWL
        return Close_TWL();
#endif
    }
    else
    {
#ifndef SDK_TWLLTD
        if (OS_IsRunOnEmulator())
        { return Close_Ensata(); }
        else
        { return Close_NITRO(); }
#endif
    }
    return FALSE;
}

//---------------------------------------------------------
BOOL
NNS_McsClose()
{
    BOOL bSuccess;

    NNS_ASSERT(IsInitialized());
    Lock();

    bSuccess = Close_InVariousDevice();

    if (bSuccess)
    {
        sDeviceCaps.deviceID = NITRODEVID_NULL; // �f�o�C�X����ID�̏�����
        SetMaskResource(0x00000000);            // ���\�[�X���ʏ��̃t���O������
    }

    Unlock();
    return bSuccess;
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsRegisterRecvCallback

  Description:  �f�[�^����M�����Ƃ��ɃR�[���o�b�N�����֐���o�^���܂��B

                �o�^����R�[���o�b�N�֐����ł̓f�[�^�̑���M���s��Ȃ��ł��������B
                �܂��A���荞�݂��֎~����Ă���ꍇ�����邽�߁A
                ���荞�ݑ҂����[�v���s��Ȃ��ł��������B

  Arguments:    pInfo:     �R�[���o�b�N�֐��̏���ێ�����\���̂ւ̃|�C���^�B
                channel:   ���[�U�[�C�ӂɌ��߂�ꂽ�f�[�^���M�̎��ʗp�̒l�B
                cbFunc:    �o�^����R�[���o�b�N�֐��B
                userData:  ���[�U�[�C�ӂ̒l�B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/
void
NNS_McsRegisterRecvCallback(
    NNSMcsRecvCBInfo*   pInfo,
    u16                 channel,
    NNSMcsRecvCallback  cbFunc,
    u32                 userData
)
{
    NNS_ASSERT(IsInitialized());
    Lock();

    NNS_ASSERT(NULL == GetRecvCBInfo(&spMcsWork->recvCBInfoList, channel));   // ���ɓ����`�����l�����g�p���Ă�����̂���������

    pInfo->channel  = channel;
    pInfo->cbFunc   = cbFunc;
    pInfo->userData = userData;

    NNS_FndAppendListObject(&spMcsWork->recvCBInfoList, pInfo);

    Unlock();
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsRegisterStreamRecvBuffer

  Description:  �f�[�^��M�p�̃o�b�t�@��o�^���܂��B
                �����ŁA�֐�NNS_McsRegisterRecvCallback()���Ăяo�����߁A
                �f�[�^��M�̃R�[���o�b�N�Ɠ����Ɏg�p�ł��܂���B
                �w�肵���o�b�t�@�ɓ����Ŏg�p���邽�߂̏��G���A���m�ۂ��܂��B
                ���̂��߁A�o�b�t�@�̃T�C�Y�͏��Ȃ��Ƃ�48�ȏ�ł���K�v������܂��B

                ��M�p�o�b�t�@����M�f�[�^�ň�t�ɂȂ�A�V�K�Ɏ�M�����f�[�^���i�[����
                �����̋󂫗e�ʂ������ꍇ�́A���̎�M�f�[�^�͎̂Ă��܂��B
                �]���āA�ʐM�Ŏg�p����f�[�^�ʂɍ��킹�ăo�b�t�@�T�C�Y���\���ȑ傫����
                �ݒ肷��K�v������܂��B

  Arguments:    channel:   ���[�U�[�C�ӂɌ��߂�ꂽ�f�[�^���M�̎��ʗp�̒l�B
                buf:       �o�^�����M�p�o�b�t�@�B
                bufSize:   �o�^�����M�p�o�b�t�@�̃T�C�Y�B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/
void
NNS_McsRegisterStreamRecvBuffer(
    u16     channel,
    void*   buf,
    u32     bufSize
)
{
    uintptr_t start = (uintptr_t)buf;
    uintptr_t end = start + bufSize;
    u8* pBBuf;
    DefRecvCBInfo* pInfo;

    NNS_ASSERT(IsInitialized());
    Lock();

    start = RoundUp(start, 4);
    end = RoundDown(end, 4);

    NNS_ASSERT(start < end);

    buf = (void*)start;
    bufSize = end - start;

    NNS_ASSERT(bufSize >= sizeof(DefRecvCBInfo) + sizeof(NNSiMcsRingBufferHeader) + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint32_t));

    pBBuf = buf;
    pInfo = buf;

    pInfo->ringBuf = NNS_McsInitRingBuffer(pBBuf + sizeof(DefRecvCBInfo), bufSize - sizeof(DefRecvCBInfo));

    NNS_McsRegisterRecvCallback(
        &pInfo->cbInfo,
        channel,
        DataRecvCallback,
        (uintptr_t)pInfo);

    Unlock();
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsUnregisterRecvResource

  Description:  NNS_McsRegisterRecvCallback()�œo�^������M�p�R�[���o�b�N�֐��A
                ���邢��NNS_McsRegisterStreamRecvBuffer()�œo�^������M�p�o�b�t�@��
                �o�^���������܂��B

  Arguments:    channel:  �R�[���o�b�N�֐���o�b�t�@��o�^����Ƃ��Ɏw�肵���l�B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/
void
NNS_McsUnregisterRecvResource(u16 channel)
{
    NNSMcsRecvCBInfo* pInfo = NULL;

    NNS_ASSERT(IsInitialized());
    Lock();

    pInfo = GetRecvCBInfo(&spMcsWork->recvCBInfoList, channel);
    NNS_ASSERT(pInfo);

    NNS_FndRemoveListObject(&spMcsWork->recvCBInfoList, pInfo);

    Unlock();
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsGetStreamReadableSize

  Description:  ��x�̊֐�NNS_McsReadStream()�Ăяo���œǂݍ��߂�f�[�^�̃T�C�Y��
                �擾���܂��B

  Arguments:    channel:    �f�[�^��M�̎��ʗp�̒l�B���[�U�[�C�ӂɌ��߂��܂��B

  Returns:      �ǂݍ��݉\�ȃf�[�^�̃T�C�Y��Ԃ��܂��B
 *---------------------------------------------------------------------------*/
u32
NNS_McsGetStreamReadableSize(u16 channel)
{
    u32 size;

    NNS_ASSERT(IsInitialized());
    Lock();

    {
        DefRecvCBInfo* pCBInfo = (DefRecvCBInfo*)GetRecvCBInfo(&spMcsWork->recvCBInfoList, channel)->userData;

        NNS_ASSERT(pCBInfo);

        size = NNS_McsGetRingBufferReadableBytes(pCBInfo->ringBuf);
    }

    Unlock();
    return size;
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsGetTotalStreamReadableSize

  Description:  ��M�p�o�b�t�@�ɂ���ǂݍ��݉\�ȃf�[�^�̃T�C�Y�̍��v���擾���܂��B

  Arguments:    channel:    �f�[�^��M�̎��ʗp�̒l�B���[�U�[�C�ӂɌ��߂��܂��B

  Returns:      �f�[�^�̃T�C�Y�̍��v��Ԃ��܂��B
 *---------------------------------------------------------------------------*/
u32
NNS_McsGetTotalStreamReadableSize(u16 channel)
{
    u32 size;

    NNS_ASSERT(IsInitialized());
    Lock();

    {
        DefRecvCBInfo* pCBInfo = (DefRecvCBInfo*)GetRecvCBInfo(&spMcsWork->recvCBInfoList, channel)->userData;

        NNS_ASSERT(pCBInfo);

        size =  NNS_McsGetRingBufferTotalReadableBytes(pCBInfo->ringBuf);
    }

    Unlock();
    return size;
}


/*---------------------------------------------------------------------------*
  Name:         NNS_McsReadStream

  Description:  �f�[�^�̎�M���s���܂��B

                ��M�����f�[�^�̒�����size�Ŏw�肵���o�b�t�@�T�C�Y���傫���ꍇ�́A
                size�Ŏw�肵�����̂݃f�[�^��ǂݍ��݂܂��B���̂Ƃ��̖߂�l�� FALSE
                �ɂȂ�܂��B�c��̃T�C�Y�́ANNS_McsGetStreamReadableSize()�ŋ��߂��܂��B

  Arguments:    channel:    �f�[�^��M�̎��ʗp�̒l�B���[�U�[�C�ӂɌ��߂��܂��B
                data:       �ǂݍ��ރf�[�^���i�[����o�b�t�@�ւ̃|�C���^�B
                size:       �ǂݍ��ރf�[�^���i�[����o�b�t�@�̃T�C�Y�B
                pReadSize:  ���ۂɓǂݍ��܂ꂽ�f�[�^�̃T�C�Y�B

  Returns:      �֐������������ꍇ�� TRUE�A���s�����ꍇ�� FALSE ��Ԃ��܂��B
 *---------------------------------------------------------------------------*/
BOOL
NNS_McsReadStream(
    u16         channel,
    void*       data,
    u32         size,
    u32*        pReadSize
)
{
    BOOL bSuccess;

    NNS_ASSERT(IsInitialized());
    Lock();

    {
        DefRecvCBInfo* pCBInfo = (DefRecvCBInfo*)GetRecvCBInfo(&spMcsWork->recvCBInfoList, channel)->userData;

        NNS_ASSERT(pCBInfo);

        bSuccess = NNS_McsReadRingBuffer(pCBInfo->ringBuf, data, size, pReadSize);
    }

    Unlock();
    return bSuccess;
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsGetStreamWritableLength

  Description:  �f�[�^���M���邽�߂̃o�b�t�@�̍ő咷���擾���܂��B
                ���̒����ȏ�͑��M�ł��܂���B

  Arguments:    pLength:  �f�[�^���M�o�b�t�@�̒���������ϐ��ւ̃|�C���^�B

  Returns:      �֐������������ꍇ�� TRUE�A���s�����ꍇ�� FALSE ���Ԃ�܂��B
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------
static u32 GetStreamWritableLength_TWL(BOOL* bSuccess)
{
    *bSuccess = TRUE;
    return ISTDSIO_MAX_PAYLOAD_SIZE;
}

//---------------------------------------------------------
static u32 GetStreamWritableLength_Ensata(BOOL* bSuccess)
{
    *bSuccess = TRUE;
    return NNS_McsGetRingBufferWritableBytes(GetEnsWorkPtr()->wrRb);
}

//---------------------------------------------------------
static u32 GetStreamWritableLength_NITRO(BOOL* bSuccess)
{
    u32 i;
    u32 length;

    // UIC�̏ꍇ�́A�f�o�C�X�I�[�v�����Ƃ̐��\�~���b�Ԃ�0��Ԃ��Ă���
    for (i = 0; i < UIC_WAIT_TIMEOUT_FRAME; ++i)
    {
        *bSuccess = 0 != NITROToolAPIStreamGetWritableLength(&length);

        if (! *bSuccess)
        {
            OS_Printf("NNS Mcs error: faild NITROToolAPIStreamGetWritableLength()\n");
            break;
        }

        if (spMcsWork->bLengthEnable)
        {
            break;
        }

        if (length > 0)
        {
            spMcsWork->bLengthEnable = TRUE;
            break;
        }

        WaitDeviceEnable();
    }
    return length;
}

//---------------------------------------------------------
static u32 GetStreamWritableLength_InVariousDevice(BOOL* bSuccess)
{
    if ( OS_IsRunOnTwl() )
    {
#ifdef SDK_TWL
        return GetStreamWritableLength_TWL(bSuccess);
#endif
    }
    else
    {
#ifndef SDK_TWLLTD
        if (OS_IsRunOnEmulator())
            { return GetStreamWritableLength_Ensata(bSuccess); }
        else
            { return GetStreamWritableLength_NITRO(bSuccess); }
#endif
    }
}

//---------------------------------------------------------
BOOL
NNS_McsGetStreamWritableLength(u32* pLength)
{
    BOOL ret = FALSE;
    u32 length;

    NNS_ASSERT(IsInitialized());
    Lock();

    length = GetStreamWritableLength_InVariousDevice(&ret);

    if (ret)
    {
        if (length < NNSi_MCS_MSG_HEAD_SIZE)
        {
            *pLength = 0;
        }
        else
        {
            *pLength = length - NNSi_MCS_MSG_HEAD_SIZE;
        }
    }

    Unlock();
    return ret;
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsWriteStream

  Description:  �f�[�^�̑��M���s���܂��B

  Arguments:    channel:  �f�[�^���M�̎��ʗp�̒l�B���[�U�[�C�ӂɌ��߂��܂��B
                data:     ���M����f�[�^���i�[����o�b�t�@�ւ̃|�C���^�B
                size:     ���M����f�[�^�̃T�C�Y�B

  Returns:      �֐������������ꍇ�� TRUE�A���s�����ꍇ�� FALSE ���Ԃ�܂��B
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------
static void WriteStream_TWL(BOOL* bSuccess, NNSiMcsMsg* pBlock, u32 length, u16 channel)
{
    if (! ISTDSIOSend(
        channel,
        (const void*)pBlock,
        NNSi_MCS_MSG_HEAD_SIZE + length)
    )
    {
        NNS_WARNING(FALSE, "NNS Mcs error: failed ISTDSIOSend()\n");
        *bSuccess = FALSE;
        return;
    }
    *bSuccess = TRUE;

}

//---------------------------------------------------------
static void WriteStream_Ensata(BOOL* bSuccess, NNSiMcsMsg* pBlock, u32 length, u16 channel)
{
    NNSiMcsEnsWork *const pWork = GetEnsWorkPtr();

    pWork->msgBuf.channel = channel;
    MI_CpuCopy8(pBlock, pWork->msgBuf.buf, NNSi_MCS_MSG_HEAD_SIZE + length);
    if (! NNS_McsWriteRingBuffer(
        pWork->wrRb,
        &pWork->msgBuf,
        offsetof(NNSiMcsEnsMsgBuf, buf) + NNSi_MCS_MSG_HEAD_SIZE + length)
    )
    {
        NNS_WARNING(FALSE, "NNS Mcs error: send error\n");
        *bSuccess = FALSE;
        return;
    }
    *bSuccess = TRUE;
}

//---------------------------------------------------------
static void WriteStream_NITRO(BOOL* bSuccess, NNSiMcsMsg* pBlock, u32 length, u16 channel)
{
    if (! NITROToolAPIWriteStream(
        channel,
        pBlock,
        NNSi_MCS_MSG_HEAD_SIZE + length)
    )
    {
        NNS_WARNING(FALSE, "NNS Mcs error: failed NITROToolAPIWriteStream()\n");
        *bSuccess = FALSE;
        return;
    }
    *bSuccess = TRUE;
}

//---------------------------------------------------------
static void WriteStream_InVariousDevice(BOOL* bSuccess, NNSiMcsMsg* pBlock, u32 length, u16 channel)
{
    if ( OS_IsRunOnTwl() )
    {
#ifdef SDK_TWL
        WriteStream_TWL(bSuccess, pBlock, length, channel);
#endif
    }
    else
    {
#ifndef SDK_TWLLTD
        if (OS_IsRunOnEmulator())
            { WriteStream_Ensata(bSuccess, pBlock, length, channel); }
        else
            { WriteStream_NITRO(bSuccess, pBlock, length, channel); }
#endif
    }
}

//---------------------------------------------------------

BOOL
NNS_McsWriteStream(
    u16         channel,
    const void* data,
    u32         size
)
{
    const u8 *const pSrc = (const u8*)data;
    int retryCnt = 0;
    u32 offset = 0;

    NNS_ASSERT(IsInitialized());
    Lock();

    // OS_Printf("NNS_McsWriteStream channel %d, size %d\n", (int)(channel), size);

    while (offset < size)
    {
        const u32 restSize = size - offset;
        u32 length;
        BOOL bSuccess;

        if (! NNS_McsGetStreamWritableLength(&length))  // 1�x�ɏ������݉\�ȃT�C�Y���擾
        {
            break;
        }

        if (restSize > length && length < NNSi_MCS_MSG_DATA_SIZE_MIN)
        {
            if (++retryCnt > SEND_RETRY_MAX)
            {
                NNS_WARNING(FALSE, "NNS Mcs error: send time out writable bytes %d, rest bytes %d\n", length, restSize);
                break;
            }
            WaitSendData(); // �������݂ł���悤�ɂȂ�܂ő҂�
        }
        else
        {
            NNSiMcsMsg* pBlock = &spMcsWork->writeBuf;

            length = min_u32(min_u32(restSize, length), NNSi_MCS_MSG_DATA_SIZE_MAX);

            pBlock->head.version = NNSi_MCS_MSG_HEAD_VERSION;
            pBlock->head.reserved = 0;
            pBlock->head.offset = offset;
            pBlock->head.totalLen = size;
            MI_CpuCopy8(pSrc + offset, pBlock->data, length);

            // OS_Printf("1 write offset %d, length [%d/%d]\n", pBlock->head.offset, length, pBlock->head.totalLen);

            bSuccess = FALSE;
            WriteStream_InVariousDevice(&bSuccess, pBlock, length, channel);
            if(!bSuccess)
            {
                break;
            }

            offset += length;
        }
    }

    Unlock();
    return offset == size;  // �Ō�܂ŏ������߂���^��Ԃ�
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsClearBuffer

  Description:  �ʐM�p�̃o�b�t�@�̓��e��j�����܂��B

  Arguments:    �Ȃ��B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------
static void ClearBuffer_TWL()
{
    // �_�~�[�̃R�[���o�b�N�֐���o�^
    ISTDSIOSetRecvCallback((ISTDSIORecvCbFunc)CallbackRecvDummy, (void*)0);

    // �{���̃R�[���o�b�N�֐����ēo�^
    ISTDSIOSetRecvCallback( (ISTDSIORecvCbFunc)CallbackRecv, (void*)&spMcsWork->recvCBInfoList );
}

//---------------------------------------------------------
static void ClearBuffer_Ensata()
{
    NNSiMcsEnsWork* pWork = GetEnsWorkPtr();
    NNS_McsClearRingBuffer(pWork->rdRb);
}

//---------------------------------------------------------
static void ClearBuffer_NITRO()
{
    // �_�~�[�̃R�[���o�b�N�֐���o�^
    BOOL bSuccess = NITROToolAPISetReceiveStreamCallBackFunction(CallbackRecvDummy, 0);
    NNS_ASSERT(bSuccess);

    NITROToolAPIPollingIdle();

    // �{���̃R�[���o�b�N�֐����ēo�^
    bSuccess = NITROToolAPISetReceiveStreamCallBackFunction(CallbackRecv, (u32)&spMcsWork->recvCBInfoList);
    NNS_ASSERT(bSuccess);
}

//---------------------------------------------------------
static void ClearBuffer_InVariousDevice()
{
    if ( OS_IsRunOnTwl() )
    {
#ifdef SDK_TWL
        ClearBuffer_TWL();
#endif
    }
    else
    {
#ifndef SDK_TWLLTD
        if (OS_IsRunOnEmulator())
            { ClearBuffer_Ensata(); }
        else
            { ClearBuffer_NITRO(); }
#endif
    }
}

//---------------------------------------------------------
void
NNS_McsClearBuffer()
{
    NNSMcsRecvCBInfo* pInfo = NULL;

    NNS_ASSERT(IsInitialized());
    Lock();

    if (sDeviceCaps.maskResource & NITROMASK_RESOURCE_POLL)
    {
        ClearBuffer_InVariousDevice();

    }

    while (NULL != (pInfo = NNS_FndGetNextListObject(&spMcsWork->recvCBInfoList, pInfo)))
    {
        if (pInfo->cbFunc == DataRecvCallback)  // �����O�o�b�t�@���g�p���Ă������
        {
            DefRecvCBInfo* pDefCBInfo = (DefRecvCBInfo*)pInfo->userData;
            NNS_McsClearRingBuffer(pDefCBInfo->ringBuf);
        }
    }

    Unlock();
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsIsServerConnect

  Description:  mcs�T�[�o��NITRO�n�[�h�E�F�A�ɑ΂��Đڑ����Ă��邩
                �ؒf���Ă��邩�̏�Ԃ�Ԃ��B

  Arguments:    �Ȃ��B

  Returns:      mcs�T�[�o��NITRO�n�[�h�E�F�A�ɐڑ����ɗ��Ă�����^�A
                �ؒf���悤�Ƃ��Ă�����U��Ԃ��B
 *---------------------------------------------------------------------------*/
BOOL
NNS_McsIsServerConnect()
{
    BOOL bSuccess;

    NNS_ASSERT(IsInitialized());
    Lock();

    NNS_McsPollingIdle();

    bSuccess = spMcsWork->bHostDataRecived;

    Unlock();
    return bSuccess;
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsPollingIdle

  Description:  ���C�����[�v���ł��̊֐����Ăяo���Ă��������B

  Arguments:    �Ȃ��B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------
static void PollingIdle_TWL()
{
    // �Ȃ�
}

//---------------------------------------------------------
static void PollingIdle_Ensata()
{
    NNSiMcsEnsWork* pWork = GetEnsWorkPtr();
    uint32_t readableBytes;
    uint32_t readBytes;

    while (0 < (readableBytes = NNS_McsGetRingBufferReadableBytes(pWork->rdRb)))
    {
        NNS_ASSERT(offsetof(NNSiMcsEnsMsgBuf, buf) < readableBytes && readableBytes <= sizeof(NNSiMcsEnsMsgBuf));

        {
            BOOL bRet = NNS_McsReadRingBuffer(pWork->rdRb, &pWork->msgBuf, readableBytes, &readBytes);
            NNS_ASSERT(bRet);
        }

        CallbackRecv((u32)&spMcsWork->recvCBInfoList, pWork->msgBuf.channel, pWork->msgBuf.buf, readBytes - offsetof(NNSiMcsEnsMsgBuf, buf));
    }
}

//---------------------------------------------------------
static void PollingIdle_NITRO()
{
    NITROToolAPIPollingIdle();
}

//---------------------------------------------------------
static void PollingIdle_InVariousDevice()
{
    if ( OS_IsRunOnTwl() )
    {
#ifdef SDK_TWL
        PollingIdle_TWL();
#endif
    }
    else
    {
#ifndef SDK_TWLLTD
        if (OS_IsRunOnEmulator())
            { PollingIdle_Ensata(); }
        else
            { PollingIdle_NITRO(); }
#endif
    }
}

//---------------------------------------------------------
void
NNS_McsPollingIdle()
{
    NNS_ASSERT(IsInitialized());
    Lock();

    if (sDeviceCaps.maskResource & NITROMASK_RESOURCE_POLL)
    {
        PollingIdle_InVariousDevice();

        if (spMcsWork->bProtocolError)
        {
            const u32 data = TRUE;  // �ڑ�
            u32 length;
            if ( NNS_McsGetStreamWritableLength(&length)
              || sizeof(data) <= length
            )
            {
                // NITRO���̃w�b�_�o�[�W������`���邽�߂Ƀ��b�Z�[�W���M
                if (NNS_McsWriteStream(NNSi_MCS_SYSMSG_CHANNEL, &data, sizeof(data)))
                {
                    // �������߂���ANITRO���͒�~���Ă���
                    OS_Panic("mcs message version error.\n");
                }
            }
        }
    }

    Unlock();
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsVBlankInterrupt

  Description:  VBlank���荞�݃n���h�����ł��̊֐����Ăяo���Ă��������B

  Arguments:    �Ȃ��B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------
static void VBlankInterruptTWL()
{

}

//---------------------------------------------------------
static void VBlankInterruptEnsata()
{

}

//---------------------------------------------------------
static void VBlankInterruptNITRO()
{
    if (sDeviceCaps.maskResource & NITROMASK_RESOURCE_VBLANK)
    {
        NITROToolAPIVBlankInterrupt();
    }
}

//---------------------------------------------------------
static void VBlankInterruptInVariousDevice()
{
    if ( OS_IsRunOnTwl() )
    {
#ifdef SDK_TWL
        VBlankInterruptTWL();
#endif
    }
    else
    {
#ifndef SDK_TWLLTD
        if (OS_IsRunOnEmulator())
            { VBlankInterruptEnsata(); }
        else
            { VBlankInterruptNITRO(); }
#endif
    }
}

//---------------------------------------------------------
void
NNS_McsVBlankInterrupt()
{
    VBlankInterruptInVariousDevice();
}

/*---------------------------------------------------------------------------*
  Name:         NNS_McsCartridgeInterrupt

  Description:  �J�[�g���b�W���荞�݃n���h�����ł��̊֐����Ăяo���Ă��������B

  Arguments:    �Ȃ��B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------
static void CartridgeInterrupt_TWL()
{
    // �Ȃ�
}

//---------------------------------------------------------
static void CartridgeInterrupt_Ensata()
{
    // �Ȃ�
}

//---------------------------------------------------------
static void CartridgeInterrupt_NITRO()
{
    if (sDeviceCaps.maskResource & NITROMASK_RESOURCE_CARTRIDGE)
    {
        NITROToolAPICartridgeInterrupt();
    }
}

//---------------------------------------------------------
static void CartridgeInterrupt_InVariousDevice()
{
    if ( OS_IsRunOnTwl() )
    {
#ifdef SDK_TWL
        CartridgeInterrupt_TWL();
#endif
    }
    else
    {
#ifndef SDK_TWLLTD
        if (OS_IsRunOnEmulator())
            { CartridgeInterrupt_Ensata(); }
        else
            { CartridgeInterrupt_NITRO(); }
#endif
    }
}

void
NNS_McsCartridgeInterrupt()
{
    CartridgeInterrupt_InVariousDevice();
}

/* #if ! defined(NNS_FINALROM) */
#endif
