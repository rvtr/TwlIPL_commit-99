#! make -f
#----------------------------------------------------------------------------
# Project:  NITRO-System - demos - g2d - Text - PortraitSW
# File:     Makefile
#
# Copyright 2004-2008 Nintendo.  All rights reserved.
#
# These coded instructions, statements, and computer programs contain
# proprietary information of Nintendo of America Inc. and/or Nintendo
# Company Ltd., and are protected by Federal copyright law.  They may
# not be disclosed to third parties or copied or duplicated in any form,
# in whole or in part, without the prior written consent of Nintendo.
#
# $Revision: 299 $
#----------------------------------------------------------------------------

NNS_USELIBS     = g2d gfd fnd

G2D_TEXTDEMOLIB	=	../textdemolib

LINCLUDES       =   $(G2D_TEXTDEMOLIB)/include
LLIBRARY_DIRS   =   $(G2D_TEXTDEMOLIB)/lib/$(NITRO_BUILDTYPE)
LLIBRARIES      =   libg2d_textdemo.a

#----------------------------------------------------------------------------

SRCS		=	main.c
TARGET_BIN	=	main.srl

MAKEROM_ROMROOT  = ../
MAKEROM_ROMFILES = ./data/*.*

#----------------------------------------------------------------------------
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs


do-build:		$(TARGETS)
$(TARGETS): $(FONT_TARGET)


include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules


#===== End of Makefile =====
