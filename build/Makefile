#! make -f
#----------------------------------------------------------------------------
# Project:  TwlFirm - build
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

include	$(TWLIPL_ROOT)/build/buildtools/commondefs


#----------------------------------------------------------------------------

SUBDIRS =	\
#           tools \				<-- Not needed unless building nandfirm
#           libraries \
#			nandfirm \			<-- Don't think this will work
#			nand_formatter \	<-- Using outdated FATFS library. I'll see
#									if I can build it sometime later but
#									right now it looks like we're missing:
#									rtfs.h, and devices/*.h
#
#									Might find in twl_wrapsdk?
			libraries_sysmenu\
			systemmenu_RED

#----------------------------------------------------------------------------

include	$(TWLIPL_ROOT)/build/buildtools/modulerules


#===== End of Makefile =====
