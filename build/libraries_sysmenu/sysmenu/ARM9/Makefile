#! make -f
#----------------------------------------------------------------------------
# Project:  TwlIPL
# File:     Makefile
#
# Copyright 2007 Nintendo.  All rights reserved.
#
# These coded instructions, statements, and computer programs contain
# proprietary information of Nintendo of America Inc. and/or Nintendo
# Company Ltd., and are protected by Federal copyright law.  They may
# not be disclosed to third parties or copied or duplicated in any form,
# in whole or in part, without the prior written consent of Nintendo.
#
# $Date:: 2007-10-03#$
# $Rev: 1319 $
# $Author: kitase_hirotake $
#----------------------------------------------------------------------------

SUBDIRS			=	

MYSUBDIRS		=	./

#----------------------------------------------------------------------------
TARGET_FIRM		=	SYSTEMMENU
TARGET_PLATFORM	=	TWL
TWL_ARCHGEN		=	LIMITED
TWL_PROC	   	=	ARM9

SRCS			=	sysmenu_lib.c sysmenu_card.c sysmenu_util.c gameBoot.c ninLogoFunc.c cmn.c \
					nitroSettingsEx.c

TARGET_LIB		=	libsysmenu$(TWL_LIBSUFFIX).a


include	$(TWLIPL_ROOT)/build/buildtools/commondefs

INSTALL_TARGETS		=	$(TARGETS)
INSTALL_DIR			=	$(SYSMENU_INSTALL_LIBDIR)

LINCLUDES		=	$(TWLSDK_ROOT)/build/libraries/mb/common/include	\
					$(TWLSDK_ROOT)/build/libraries/spi/ARM9/include		\

#----------------------------------------------------------------------------

do-build: $(MYSUBDIRS) $(TARGETS)

include	$(TWLIPL_ROOT)/build/buildtools/modulerules


$(MYSUBDIRS)::
#	$(MAKE) -C $@ -f MakeCrt0

#===== End of Makefile =====
