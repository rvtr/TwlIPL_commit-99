/*---------------------------------------------------------------------------*
  Project:  TwlFirm - nandfirm - sdmc-launcher
  File:     main.c

  Copyright 2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Date::            $
  $Rev$
  $Author$
 *---------------------------------------------------------------------------*/
#include <firm.h>
#include <twl/os/ARM7/debugLED.h>

#define FATFS_HEAP_SIZE     (64*1024)   // FATFS用ヒープ (サイズ調整必要)

#define BOOT_DEVICE     FATFS_MEDIA_TYPE_SD
#define PARTITION_NO    0                       // 0固定
#define MENU_FILE       (char*)L"A:\\menu.srl"          // 対象ファイル(DRIVE_LETTERと合わせること)
#define MENU_FILE_A     (char*)L"A:\\menu_a.srl"        // 対象ファイル(DRIVE_LETTERと合わせること)
#define MENU_FILE_B     (char*)L"A:\\menu_b.srl"        // 対象ファイル(DRIVE_LETTERと合わせること)
#define MENU_FILE_L     (char*)L"A:\\menu_l.srl"        // 対象ファイル(DRIVE_LETTERと合わせること)
#define MENU_FILE_R     (char*)L"A:\\menu_r.srl"        // 対象ファイル(DRIVE_LETTERと合わせること)

#define DRIVE_LETTER    'A'                     // マウント先ドライブ名
#define DRIVE_NO        (DRIVE_LETTER - 'A')    // マウント先ドライブ番号

static u8 fatfsHeap[FATFS_HEAP_SIZE] __attribute__ ((aligned (32)));

static SDPortContextData nandContext;   // 一時待避用 (次に渡すならSHAREDのどこかのアドレスにする)

#ifndef SDK_FINALROM
static u8 step = 0x80;
#endif

/*
    Profile
*/
#ifndef SDK_FINALROM
#define PROFILE_MAX  0x100
u32 profile[PROFILE_MAX];
u32 pf_cnt = 0;
#endif

/***************************************************************
    PreInit

    FromBootの対応をまとめる＆メインメモリの初期化
    OS_Init前なので注意 (ARM9によるメインメモリ初期化で消されないように注意)
***************************************************************/
static void PreInit(void)
{

    /*
        FromBrom関連
    */

    // NANDパラメータの待避
    nandContext = OSi_GetFromBromAddr()->SDNandContext;

    MIi_CpuClearFast( 0, (void*)OSi_GetFromBromAddr(), sizeof(OSFromBromBuf) );
}

/***************************************************************
    EraseAll

    不正終了しました
    いろいろ消してください
    DSモードにして終わるのがよいか？
***************************************************************/
static void EraseAll(void)
{
#ifdef SDK_FINALROM
    // TODO
#endif
}

void TwlSpMain( void )
{
    // OS_InitDebugLED and OS_SetDebugLED are able to call after OS_Init
#ifndef SDK_FINALROM
    I2Ci_WriteRegister(I2C_SLAVE_DEBUG_LED, 0x03, 0x00);
    I2Ci_WriteRegister(I2C_SLAVE_DEBUG_LED, 0x01, ++step);
#endif

    PreInit();

#ifndef SDK_FINALROM
    I2Ci_WriteRegister(I2C_SLAVE_DEBUG_LED, 0x01, ++step);

    // 0: before PXI
    profile[pf_cnt++] = (u32)OS_TicksToMicroSecondsBROM(OS_GetTick());
#endif

    OS_InitFIRM();
    OS_EnableIrq(); // PMでOS_InitTick()を使っているので (他でも使ってる？)

#ifndef SDK_FINALROM
    //OS_EnableIrq();
    // 1: after PXI
    profile[pf_cnt++] = (u32)OS_TicksToMicroSeconds(OS_GetTick());
#endif

    OS_SetDebugLED(++step);

    PM_InitFIRM();
    PM_BackLightOn( FALSE );

#ifndef SDK_FINALROM
    // 2: after PM
    profile[pf_cnt++] = (u32)OS_TicksToMicroSeconds(OS_GetTick());
#endif

    OS_SetDebugLED(++step);

    /* FATFSライブラリ用にカレントヒープを設定 */
    /* WRAM上のfatfsHeapをメインメモリヒープとして登録している */
    {
        OSHeapHandle hh;
        u8     *lo = (u8*)fatfsHeap;
        u8     *hi = (u8*)fatfsHeap + FATFS_HEAP_SIZE;
        lo = OS_InitAlloc(OS_ARENA_MAIN_SUBPRIV, lo, hi, 1);
        OS_SetArenaLo(OS_ARENA_MAIN_SUBPRIV, lo);
        hh = OS_CreateHeap(OS_ARENA_MAIN_SUBPRIV, OS_GetSubPrivArenaLo(), hi);
        OS_SetCurrentHeap(OS_ARENA_MAIN_SUBPRIV, hh);
    }

    OS_SetDebugLED(++step);

    if ( FATFS_InitFIRM( &nandContext ) )
    {
#ifndef SDK_FINALROM
        // 3: after FATFS
        profile[pf_cnt++] = (u32)OS_TicksToMicroSeconds(OS_GetTick());
#endif
        OS_SetDebugLED(++step);
        PM_BackLightOn( FALSE );

        if ( FATFS_MountDriveFIRM( DRIVE_NO, BOOT_DEVICE, PARTITION_NO ) )
        {
            BOOL result;
#ifndef SDK_FINALROM
            // 4: after Mount
            profile[pf_cnt++] = (u32)OS_TicksToMicroSeconds(OS_GetTick());
#endif
            OS_SetDebugLED(++step);
            PM_BackLightOn( FALSE );

            switch ( PAD_Read() & PAD_KEYPORT_MASK )
            {
            case 0:
                result = FATFS_OpenSpecifiedSrl( MENU_FILE );
                break;
            case PAD_BUTTON_A:
                result = FATFS_OpenSpecifiedSrl( MENU_FILE_A );
                break;
            case PAD_BUTTON_B:
                result = FATFS_OpenSpecifiedSrl( MENU_FILE_B );
                break;
            case PAD_BUTTON_L:
                result = FATFS_OpenSpecifiedSrl( MENU_FILE_L );
                break;
            case PAD_BUTTON_R:
                result = FATFS_OpenSpecifiedSrl( MENU_FILE_R );
                break;
            default:
                OS_SetDebugLED( (u8)(PAD_Read() & PAD_KEYPORT_MASK) );
                OS_Terminate();
                break;
            }

            if ( result )
            {
#ifndef SDK_FINALROM
                // 5: after Open
                profile[pf_cnt++] = (u32)OS_TicksToMicroSeconds(OS_GetTick());
#endif
                OS_SetDebugLED(++step);
                PM_BackLightOn( FALSE );

                if ( FATFS_LoadHeader() && FATFS_LoadStatic() )
                {
#ifndef SDK_FINALROM
                    // 127: before Boot
                    pf_cnt = PROFILE_MAX-1;
                    profile[pf_cnt++] = (u32)OS_TicksToMicroSeconds(OS_GetTick());
                    {
                        int i;
                        PXI_RecvID();
                        OS_TPrintf("\n[ARM7] Begin\n");
                        for (i = 0; i < PROFILE_MAX; i++)
                        {
                            OS_TPrintf("0x%08X\n", profile[i]);
                        }
                        OS_TPrintf("\n[ARM7] End\n");
                    }
#endif
                    OS_SetDebugLED(++step);
                    PM_BackLightOn( TRUE ); // last chance

                    FATFS_Boot();
                }
            }
        }
    }

    OS_SetDebugLED( (u8)(0xF0 | step));

    EraseAll();

    // failed
    while (1)
    {
        PXI_NotifyID( FIRM_PXI_ID_NULL );
    }
}

