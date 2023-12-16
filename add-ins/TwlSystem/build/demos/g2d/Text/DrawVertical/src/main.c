/*---------------------------------------------------------------------------*
  Project:  NITRO-System - demos - g2d - Text - DrawVertical
  File:     main.c

  Copyright 2004-2008 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 172 $
 *---------------------------------------------------------------------------*/

// ============================================================================
//  �f���̓��e
//      �c�����p�ɕϊ������t�H���g���g�p���ďc�����`����s���܂��B
//      ���̃f���͓��{�����p�ł��B
//
//  ������@
//      �\���{�^���̉�������������ʏ�ƂȂ�悤��
//      �t�H���g�ƕ\���ʒu��؂�ւ��܂��B
//      A �{�^���������Əc����/��������؂�ւ��܂��B
// ============================================================================


#include <nnsys/g2d/g2d_TextCanvas.h>
#include <nnsys/g2d/g2d_CharCanvas.h>
#include "g2d_textdemolib.h"


#define CHARACTER_WIDTH     8
#define CHARACTER_HEIGHT    8

#define CANVAS_WIDTH        28      // �����`���̕�    (�L�����N�^�P��)
#define CANVAS_HEIGHT       20      // �����`���̍���  (�L�����N�^�P��)
#define CANVAS_LEFT         2       // �����`���̈ʒuX (�L�����N�^�P��)
#define CANVAS_TOP          2       // �����`���̈ʒuY (�L�����N�^�P��)

#define BG_WIDTH            32      // �������`�悷�� BG �̕�   (�L�����N�^�P��)
#define BG_HEIGHT           32      // �������`�悷�� BG �̍��� (�L�����N�^�P��)

#define TEXT_HSPACE         1       // ������`�掞�̕����� (�s�N�Z���P��)
#define TEXT_VSPACE         1       // ������`�掞�̍s��   (�s�N�Z���P��)

#define CHARACTER_OFFSET    1       // �g�p����L�����N�^��̊J�n�ԍ�


//------------------------------------------------------------------------------
// �^

typedef enum Direction
{
    DIR_H_0,    // ������ ��ʂ̍�����E��
    DIR_H_90,   // ������ ��ʂ̏ォ�牺
    DIR_H_180,  // ������ ��ʂ̉E���獶��
    DIR_H_270,  // ������ ��ʂ̉�������
    DIR_V_0,    // �c���� ��ʂ̏ォ�牺��
    DIR_V_90,   // �c���� ��ʂ̉E���獶��
    DIR_V_180,  // �c���� ��ʂ̉�������
    DIR_V_270,  // �c���� ��ʂ̍�����E��
    DIR_NULL
}
Direction;

typedef struct FontInfo
{
    const char* name;
    Direction   dir;
    NNSG2dFont  res;
}
FontInfo;


//------------------------------------------------------------------------------
// �O���[�o���ϐ�

NNSG2dCharCanvas        gCanvas;        // CharCanvas
NNSG2dTextCanvas        gTextCanvas;    // TextCanvas

FontInfo gFonts[] =
{
    {"/data/h_0.NFTR",   DIR_H_0 },
    {"/data/h_90.NFTR",  DIR_H_90 },
    {"/data/h_180.NFTR", DIR_H_180 },
    {"/data/h_270.NFTR", DIR_H_270 },

    {"/data/v_0.NFTR",   DIR_V_0 },
    {"/data/v_90.NFTR",  DIR_V_90 },
    {"/data/v_180.NFTR", DIR_V_180 },
    {"/data/v_270.NFTR", DIR_V_270 },
};

// �\�����镶����
const char* const sSampleText = "����͂ɂقւ� ����ʂ�� �킩�悽�ꂻ\n"
                                "�˂Ȃ�� ����̂������ ���ӂ�����\n"
                                "��������߂݂� ��Ђ�����\n"
                                "The quick brown fox jumps over the lazy dog";




//****************************************************************************
// Initialize etc.
//****************************************************************************

/*---------------------------------------------------------------------------*
  Name:         InitScreen

  Description:  BG �ʂ�ݒ肵�܂��B

  Arguments:    �Ȃ��B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/
static void InitScreen(void)
{
    // BG 1 ��ݒ�
    G2_SetBG1Control(
        GX_BG_SCRSIZE_TEXT_256x256,     // �X�N���[���T�C�Y 256x256
        GX_BG_COLORMODE_16,             // �J���[���[�h     16�F
        GX_BG_SCRBASE_0x0000,           // �X�N���[���x�[�X
        GX_BG_CHARBASE_0x00000,         // �L�����N�^�x�[�X
        GX_BG_EXTPLTT_01                // �g���p���b�g�X���b�g
    );

    // BG1 ������
    CMN_SetPlaneVisible( GX_PLANEMASK_BG1 );

    // �J���[�p���b�g��ݒ�
    GX_LoadBGPltt(TXTColorPalette, 0, sizeof(TXTColorPalette));
}



/*---------------------------------------------------------------------------*
  Name:         InitCanvas

  Description:  ������`��̏����������܂��B

  Arguments:    �Ȃ��B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/
static void InitCanvas(void)
{
    GXCharFmt16*  pChrBase = (GXCharFmt16*) G2_GetBG1CharPtr();
    GXScrFmtText* pScrBase = (GXScrFmtText*)G2_GetBG1ScrPtr();
    int cOffset = CHARACTER_OFFSET;

    // �X�N���[�����N���A
    MI_CpuClear16(G2_GetBG1ScrPtr(), sizeof(GXScrFmtText) * BG_WIDTH * BG_HEIGHT);

    // CharCanvas �̏�����
    NNS_G2dCharCanvasInitForBG(
        &gCanvas,
        pChrBase + cOffset,
        CANVAS_WIDTH,
        CANVAS_HEIGHT,
        NNS_G2D_CHARA_COLORMODE_16
    );

    // TextCanvas�̏�����
    NNS_G2dTextCanvasInit(
        &gTextCanvas,
        &gCanvas,
        &gFonts[0].res,
        TEXT_HSPACE,
        TEXT_VSPACE
    );

    // �X�N���[����ݒ�
    NNS_G2dMapScrToCharText(
        pScrBase,
        CANVAS_WIDTH,
        CANVAS_HEIGHT,
        CANVAS_LEFT,
        CANVAS_TOP,
        NNS_G2D_TEXT_BG_WIDTH_256,
        cOffset,
        TXT_CPALETTE_4BPP
    );
}



/*---------------------------------------------------------------------------*
  Name:         SampleDraw

  Description:  �T���v���������`�悵�܂��B

  Arguments:    x:      �`�悷��ʒu x
                y:      �`�悷��ʒu y
                pFont:  �`��Ɏg�p����t�H���g

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/
static void SampleDraw(int x, int y, const NNSG2dFont* pFont)
{
    // �w�i�N���A
    NNS_G2dCharCanvasClear(&gCanvas, TXT_COLOR_4BPP_BG);

    // �t�H���g�ύX
    NNS_G2dTextCanvasSetFont(&gTextCanvas, pFont);

    // �e�L�X�g�`��
    NNS_G2dTextCanvasDrawText(&gTextCanvas, x, y, TXT_COLOR_4BPP_TEXT,
            TXT_DRAWTEXT_FLAG_DEFAULT, sSampleText);
}



/*---------------------------------------------------------------------------*
  Name:         SampleInit

  Description:  �T���v���̏����ݒ菈���ł��B

  Arguments:    �Ȃ��B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/
static void SampleInit(void)
{
    int i;

    // �t�H���g�ǂݍ���
    for( i = 0; i < ARY_SIZEOF(gFonts); ++i )
    {
        TXT_LoadFont( &gFonts[i].res, gFonts[i].name );
    }


    // �X�N���[���ݒ�
    InitScreen();

    // �L�����o�X�\�z
    InitCanvas();
}



/*---------------------------------------------------------------------------*
  Name:         SearchFont

  Description:  �w�肳�ꂽ�����p�̃t�H���g��T���܂��B

  Arguments:    pfis:   �t�H���g���̔z��
                dir:    �Ώۂ̕���

  Returns:      ���������t�H���g��Ԃ��܂��B
 *---------------------------------------------------------------------------*/
static const NNSG2dFont* SearchFont(const FontInfo* pfis, Direction dir)
{
    int i;

    for( i = 0; i < ARY_SIZEOF(gFonts); ++i )
    {
        if( pfis[i].dir == dir )
        {
            return &pfis[i].res;
        }
    }

    return NULL;
}



/*---------------------------------------------------------------------------*
  Name:         MakeDirection

  Description:  �`������Əc����/��������g�ݍ��킹�܂��B

  Arguments:    d:  �`�����
                bV: �c�����Ȃ� TRUE�A�������Ȃ� FALSE

  Returns:      �`������Əc����/��������g�ݍ��킹���l��Ԃ��܂��B
 *---------------------------------------------------------------------------*/
static Direction MakeDirection(Direction d, BOOL bV)
{
    switch( d )
    {
    case DIR_H_0:   return bV ? DIR_V_0:    DIR_H_0;
    case DIR_H_90:  return bV ? DIR_V_90:   DIR_H_90;
    case DIR_H_180: return bV ? DIR_V_180:  DIR_H_180;
    case DIR_H_270: return bV ? DIR_V_270:  DIR_H_270;
    }

    return DIR_H_0;
}



/*---------------------------------------------------------------------------*
  Name:         SampleMain

  Description:  �T���v���̃��C�������ł��B

  Arguments:    �Ȃ��B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/
static void SampleMain(void)
{
    static Direction rotation = DIR_NULL;
    static BOOL bV = FALSE;
    BOOL bUpdated = FALSE;

    //---- ���͂ɉ����ĕ\���̕�����ύX���܂��B
    if( CMN_IsTrigger(PAD_KEY_UP) || rotation == DIR_NULL )
    {
        rotation = DIR_H_0;
        bUpdated = TRUE;
    }
    if( CMN_IsTrigger(PAD_KEY_DOWN) )
    {
        rotation = DIR_H_180;
        bUpdated = TRUE;
    }
    if( CMN_IsTrigger(PAD_KEY_LEFT) )
    {
        rotation = DIR_H_270;
        bUpdated = TRUE;
    }
    if( CMN_IsTrigger(PAD_KEY_RIGHT) )
    {
        rotation = DIR_H_90;
        bUpdated = TRUE;
    }
    if( CMN_IsTrigger(PAD_BUTTON_A) )
    {
        bV = ! bV;
        bUpdated = TRUE;
    }


    //---- �������ύX���ꂽ�ꍇ�ɕύX�𔽉f���܂��B
    if( bUpdated )
    {
        static const int canvas_width  = CANVAS_WIDTH  * CHARACTER_WIDTH;
        static const int canvas_height = CANVAS_HEIGHT * CHARACTER_HEIGHT;
        const Direction dir = MakeDirection(rotation, bV);
        const NNSG2dFont* pFont = SearchFont(gFonts, dir);
        int x = 0;
        int y = 0;

        NNS_G2D_POINTER_ASSERT( pFont );

        //---- �����ɉ����Ďn�_�𒲐����܂��B
        switch( dir )
        {
        case DIR_H_270:
        case DIR_V_180: y = canvas_height;  break;
        case DIR_H_90:
        case DIR_V_0:   x = canvas_width;  break;
        case DIR_H_180:
        case DIR_V_90:  x = canvas_width;
                        y = canvas_height;  break;
        }

        //---- �����ʂ̃t�H���g��p���ăT���v���������`�悵�܂��B
        SampleDraw(x, y, pFont);


        //---- ���b�Z�[�W�\��
        DTX_PrintLine("DrawVertical demo");
        DTX_PrintLine("  operation:");
        DTX_PrintLine("    +: change direction");
        DTX_PrintLine("    A: toggle horizontal/vertical writing");
        DTX_PrintLine("");
        DTX_PrintLine("direction:");
        switch( dir )
        {
        case DIR_H_0:
        case DIR_V_270: DTX_PrintLine("  left to right"); break;
        case DIR_H_90:
        case DIR_V_0:   DTX_PrintLine("  top to bottom"); break;
        case DIR_H_180:
        case DIR_V_90:  DTX_PrintLine("  right to left"); break;
        case DIR_H_270:
        case DIR_V_180: DTX_PrintLine("  bottom to up");  break;
        }
        DTX_PrintLine("");
        DTX_PrintLine("writing mode:");
        DTX_PrintLine(bV ? "  vertical": "  horizontal");
    }
}


//****************************************************************************
// Main
//****************************************************************************


/*---------------------------------------------------------------------------*
  Name:         NitroMain

  Description:  ���C���֐��ł��B

  Arguments:    �Ȃ��B

  Returns:      �Ȃ��B
 *---------------------------------------------------------------------------*/
void NitroMain(void)
{
    // Initilizing App.
    {
        // SDK �ƃf�����C�u������������
        OS_Init();
        TXT_Init();

        // �w�i��ݒ�
        TXT_SetupBackground();

        // �f���p�̑O����
        SampleInit();
    }

    // start display
    {
        CMN_WaitVBlankIntr();
        GX_DispOn();
        GXS_DispOn();
    }

    // Main loop
    while( TRUE )
    {
        CMN_ReadGamePad();

        CMN_WaitVBlankIntr();
        SampleMain();

        // ���o�͂̕\��
        DTX_Reflect();
    }
}
