/*---------------------------------------------------------------------------*
  Project:  NITRO-System - demos - snd - simple
  File:     main.c

  Copyright 2004-2008 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 172 $
 *---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
// USAGE:
//  A : start Bgm
//  B : stop Bgm
//  Up   : start one shot SE No.0
//---------------------------------------------------------------------------

#include <nitro.h>
#include <nitro/fs.h>
#include <nnsys/snd.h>

#include "../../data/sound_data.sadl"

#define SOUND_HEAP_SIZE 0x80000
#define STREAM_THREAD_PRIO 10

static NNSSndArc arc;
static u8 sndHeap[ SOUND_HEAP_SIZE ];

static NNSSndHeapHandle heap;

static NNSSndHandle bgmHandle;
static NNSSndHandle seHandle;

u16 Cont;
u16 Trg;

void VBlankIntr( void );

//----------------------------------------------------------------
//   NitroMain
//
void NitroMain()
{
    OS_Init();
    GX_Init();
    
    // VBlank settings
    OS_SetIrqFunction(OS_IE_V_BLANK, VBlankIntr);
    (void)OS_EnableIrqMask( OS_IE_V_BLANK );
    (void)OS_EnableIrq();
    (void)GX_VBlankIntr(TRUE);
    
    FS_Init( MI_DMA_MAX_NUM );
    
    // Initialize sound
    NNS_SndInit();
    heap = NNS_SndHeapCreate( & sndHeap, sizeof( sndHeap ) );
    NNS_SndArcInit( &arc, "/sound_data.sdat", heap, FALSE );
    (void)NNS_SndArcPlayerSetup( heap );
    NNS_SndArcStrmInit( STREAM_THREAD_PRIO, heap );
    
    // Load sound data
    (void)NNS_SndArcLoadSeq( SEQ_MARIOKART64_TITLE, heap );
    (void)NNS_SndArcLoadSeqArc( SEQ_SE, heap );
    (void)NNS_SndArcLoadBank( BANK_SE, heap );
    
    // Initialize sound handle
    NNS_SndHandleInit( &bgmHandle );
    NNS_SndHandleInit( &seHandle );
    
    // dummy pad read
    Cont = PAD_Read();
    
    // print usage
    OS_Printf("=================================\n");
    OS_Printf("USAGE:\n");
    OS_Printf(" A : start Bgm\n");
    OS_Printf(" B : stop Bgm\n");
    OS_Printf(" Up : start SE\n");
    OS_Printf("=================================\n");
    
    //================ Main Loop
    while(1)
    {
        u16 ReadData;
        
        SVC_WaitVBlankIntr();
        
        ReadData = PAD_Read();
        Trg  = (u16)(ReadData & (ReadData ^ Cont));
        Cont = ReadData;
        
        if ( Trg & PAD_BUTTON_A ) {
            // start BGM
            (void)NNS_SndArcPlayerStartSeq( &bgmHandle, SEQ_MARIOKART64_TITLE );
        }
        if ( Trg & PAD_BUTTON_B ) {
            // stop BGM
            (void)NNS_SndPlayerStopSeq( &bgmHandle, 1 );
        }
        
        if ( Trg & PAD_KEY_UP ) {
            // start SE
            (void)NNS_SndArcPlayerStartSeqArc( &seHandle, SEQ_SE, SE_COIN );
        }
        
        //---- framework
        NNS_SndMain();
    }
}

//---------------------------------------------------------------------------
// VBlank interrupt function:
//
// Interrupt handlers are registered on the interrupt table by OS_SetIRQFunction.
// OS_EnableIrqMask selects IRQ interrupts to enable, and
// OS_EnableIrq enables IRQ interrupts.
// Notice that you have to call 'OS_SetIrqCheckFlag' to check a VBlank interrupt.
//---------------------------------------------------------------------------
void VBlankIntr(void)
{
    OS_SetIrqCheckFlag( OS_IE_V_BLANK );                   // checking VBlank interrupt
}

