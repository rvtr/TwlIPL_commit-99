#! make -f
#----------------------------------------------------------------------------
# Project:  NITRO-System - demos - mcs - file_io - nitro
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
# $Revision: 563 $
#----------------------------------------------------------------------------

NNS_USELIBS = fnd mcs

SUBDIRS		=


#----------------------------------------------------------------------------

SRCS		=	main.c


TARGET_BIN	=	main.srl

NNS_MCS_DEMOS_FILEIO_DATA_DIR = $(call eupath,$(NITROSYSTEM_ROOT)/build/demos/mcs/file_io/nitro/data)

include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs


#----------------------------------------------------------------------------

do-build:		$(TARGETS)
# data/test.txt が存在しない場合にコピーする .
	if [ ! data -ef $(NNS_MCS_DEMOS_FILEIO_DATA_DIR) ] ;	\
	then													\
		mkdir -p $(NNS_MCS_DEMOS_FILEIO_DATA_DIR) ;			\
		cp data/test.txt $(NNS_MCS_DEMOS_FILEIO_DATA_DIR) ;	\
	fi

include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules


#===== End of Makefile =====
