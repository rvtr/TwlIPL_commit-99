#! make -f
#----------------------------------------------------------------------------
# Project:  TwlIPL - libraries - init
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
# $Date::            $
# $Rev:$
# $Author:$
#----------------------------------------------------------------------------

SUBDIRS			=
#SUBMAKES		= Makefile.CALLTRACE 	\
#			  Makefile.FUNCTIONCOST

#----------------------------------------------------------------------------

# build ARM & THUMB libraries
FIRM_CODEGEN_ALL 	?= TRUE

SRCS			= crt0_firm.c \

TARGET_OBJ		= crt0_firm.o

#----------------------------------------------------------------------------

# DEBUG版ビルドの場合、RELEASE版でビルドして
# DEBUG版のライブラリを装います。

ifdef	NITRO_DEBUG
NITRO_BUILD_TYPE	= RELEASE
endif

include	$(TWLIPL_ROOT)/build/buildtools/commondefs

INSTALL_TARGETS		= $(TARGETS)
INSTALL_DIR		= $(FIRM_INSTALL_LIBDIR)


#----------------------------------------------------------------------------

do-build:		$(TARGETS)

include	$(TWLIPL_ROOT)/build/buildtools/modulerules


#===== End of Makefile =====
