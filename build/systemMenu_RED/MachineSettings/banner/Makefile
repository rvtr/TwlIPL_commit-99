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

include $(TWLSDK_ROOT)/build/buildtools/commondefs

ICON_DIR			= ./icon
TOOLS_DIR			= $(TWLIPL_ROOT)/tools/bin
NTEXCONV			= $(TOOLS_DIR)/ntexconv.exe
MAKEBANNER			= $(TOOLS_DIR)/makebanner.exe

BANNER_ICON			= $(ICON_DIR)/gameIcon.bmp
BANNER_SPEC			= banner_v3.bsf

TARGETS				= banner.bnr
INSTALL_DIR			= ./
INSTALL_TARGETS		= $(TARGETS)

BANNER_ICON_NAME	= $(basename $(BANNER_ICON))

LDIRT_CLEAN			= $(TARGETS) \
					  $(BANNER_ICON_NAME).nbfs \
					  $(BANNER_ICON_NAME).nbfc \
					  $(BANNER_ICON_NAME).nbfp \
					  $(TARGETS:.bnr=.srl)

include $(TWLSDK_ROOT)/build/buildtools/modulerules

#----------------------------------------------------------------------------
#  build
#----------------------------------------------------------------------------
do-build:		$(TARGETS)

$(TARGETS):		$(BANNER_SPEC) $(BANNER_ICON)
				$(NTEXCONV) -no -bg -bgb -bgnc $(BANNER_ICON) >/dev/null && \
				$(MAKEBANNER) -d -N $(BANNER_ICON_NAME) $(BANNER_SPEC) $(TARGETS)

#
