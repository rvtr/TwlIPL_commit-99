#! make -f
#----------------------------------------------------------------------------
# Project:  NITRO-System - demos - g3d - samples - CustomizeSbcOp
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

NNS_USELIBS     = g3d gfd fnd

G3D_DEMOLIB		=	$(NITROSYSTEM_G3D_ROOT)/build/demos/g3d/demolib

LINCLUDES       =   $(G3D_DEMOLIB)/include
LLIBRARY_DIRS   =   $(G3D_DEMOLIB)/lib/$(NITRO_BUILDTYPE)
LLIBRARIES      =   libg3d_demo.a

#----------------------------------------------------------------------------

SUBDIRS	= 

SRCS		=	main.c
TARGET_BIN	=	main.srl

MAKEROM_ROMROOT  = ./
MAKEROM_ROMFILES = $(G3D_DATABIN)*.*

G3D_DATABIN = data/
G3D_DATASRC = data/src

G3D_IMD = data/src/billboard.imd
G3D_ICA =
G3D_IVA =
G3D_IMA =
G3D_ITP =
G3D_ITA =

G3D_NSBMD_TMP = $(G3D_IMD:.imd=.nsbmd)
G3D_NSBCA_TMP = $(G3D_ICA:.ica=.nsbca)
G3D_NSBVA_TMP = $(G3D_IVA:.iva=.nsbva)
G3D_NSBMA_TMP = $(G3D_IMA:.ima=.nsbma)
G3D_NSBTP_TMP = $(G3D_ITP:.itp=.nsbtp)
G3D_NSBTA_TMP = $(G3D_ITA:.ita=.nsbta)

G3D_NSBMD = $(subst src/,,$(G3D_NSBMD_TMP))
G3D_NSBCA = $(subst src/,,$(G3D_NSBCA_TMP))
G3D_NSBVA = $(subst src/,,$(G3D_NSBVA_TMP))
G3D_NSBMA = $(subst src/,,$(G3D_NSBMA_TMP))
G3D_NSBTP = $(subst src/,,$(G3D_NSBTP_TMP))
G3D_NSBTA = $(subst src/,,$(G3D_NSBTA_TMP))

LDIRT_CLEAN = $(G3D_NSBMD) $(G3D_NSBCA) $(G3D_NSBVA) $(G3D_NSBMA) $(G3D_NSBTP) $(G3D_NSBTA)

#----------------------------------------------------------------------------
include	$(NITROSYSTEM_ROOT)/build/buildtools/commondefs


do-build: $(TARGETS)
$(TARGETS): binData
binData: $(G3D_NSBMD) $(G3D_NSBCA) $(G3D_NSBVA) $(G3D_NSBMA) $(G3D_NSBTP) $(G3D_NSBTA)
%.nsbmd: $(subst data/,data/src/,$(@:.nsbmd=.imd))
	$(NITROSYSTEM_TOOLSDIR)/bin/g3dcvtr.exe $(subst data/,data/src/,$(@:.nsbmd=.imd)) -o $@
%.nsbca: $(subst data/,data/src/,$(@:.nsbca=.ica))
	$(NITROSYSTEM_TOOLSDIR)/bin/g3dcvtr.exe $(subst data/,data/src/,$(@:.nsbca=.ica)) -o $@
%.nsbva: $(subst data/,data/src/,$(@:.nsbva=.iva))
	$(NITROSYSTEM_TOOLSDIR)/bin/g3dcvtr.exe $(subst data/,data/src/,$(@:.nsbva=.iva)) -o $@
%.nsbma: $(subst data/,data/src/,$(@:.nsbma=.ima))
	$(NITROSYSTEM_TOOLSDIR)/bin/g3dcvtr.exe $(subst data/,data/src/,$(@:.nsbma=.ima)) -o $@
%.nsbtp: $(subst data/,data/src/,$(@:.nsbtp=.itp))
	$(NITROSYSTEM_TOOLSDIR)/bin/g3dcvtr.exe $(subst data/,data/src/,$(@:.nsbtp=.itp)) -o $@
%.nsbta: $(subst data/,data/src/,$(@:.nsbta=.ita))
	$(NITROSYSTEM_TOOLSDIR)/bin/g3dcvtr.exe $(subst data/,data/src/,$(@:.nsbta=.ita)) -o $@


include	$(NITROSYSTEM_ROOT)/build/buildtools/modulerules


#===== End of Makefile =====
