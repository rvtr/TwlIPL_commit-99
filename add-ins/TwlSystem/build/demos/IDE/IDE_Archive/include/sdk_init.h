/*---------------------------------------------------------------------------*
  Project:  NITRO-System - demos - IDE - IDE_Archive
  File:     sdk_init.h

  Copyright 2004-2008 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Revision: 172 $
 *---------------------------------------------------------------------------*/

#ifndef SDK_INIT_H_
#define SDK_INIT_H_

// プリコンパイルヘッダを使用する。
// #include <nitro.h>

#ifdef __cplusplus
extern "C" {
#endif


void	VBlankIntr(void);

void	InitSystem(void);
void	InitVRAM(void);
void	InitDisplay(void);


#ifdef __cplusplus
}/* extern "C" */
#endif

// SDK_INIT_H_
#endif
