#! make -f
#----------------------------------------------------------------------------
# Project:  NITRO-System - demos - fnd - archive2
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
# $Revision: 172 $
#----------------------------------------------------------------------------

NNS_USELIBS = fnd

SUBDIRS		=


#----------------------------------------------------------------------------

SRCS			=	main.c sdk_init.c nns_util.c
TARGET_BIN		=	main.srl

MAKEROM_ROMROOT  = ./
MAKEROM_ROMFILES = data/*.*

include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs


#----------------------------------------------------------------------------

do-build:	$(TARGETS)

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules


#===== End of Makefile =====
