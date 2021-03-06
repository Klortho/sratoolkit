# ===========================================================================
#
#                            PUBLIC DOMAIN NOTICE
#               National Center for Biotechnology Information
#
#  This software/database is a "United States Government Work" under the
#  terms of the United States Copyright Act.  It was written as part of
#  the author's official duties as a United States Government employee and
#  thus cannot be copyrighted.  This software/database is freely available
#  to the public for use. The National Library of Medicine and the U.S.
#  Government have not placed any restriction on its use or reproduction.
#
#  Although all reasonable efforts have been taken to ensure the accuracy
#  and reliability of the software and data, the NLM and the U.S.
#  Government do not and cannot warrant the performance or results that
#  may be obtained by using this software or data. The NLM and the U.S.
#  Government disclaim all warranties, express or implied, including
#  warranties of performance, merchantability or fitness for any particular
#  purpose.
#
#  Please cite the author in any work or product based on this material.
#
# ===========================================================================


default: std

TOP ?= $(shell ../../build/abspath.sh ../..)
MODULE = tools/kar

include $(TOP)/build/Makefile.env

INT_TOOLS = \

EXT_TOOLS = \
	kar \
	sra-kar

ALL_TOOLS = \
	$(INT_TOOLS) \
	$(EXT_TOOLS)

#-------------------------------------------------------------------------------
# outer targets
#
all std: vers-includes
	@ $(MAKE_CMD) $(TARGDIR)/std

$(ALL_TOOLS): vers-includes
	@ $(MAKE_CMD) $(BINDIR)/$@

.PHONY: all std $(ALL_TOOLS)

#-------------------------------------------------------------------------------
# std
#
$(TARGDIR)/std: \
	$(addprefix $(BINDIR)/,$(ALL_TOOLS))

.PHONY: $(TARGDIR)/std

#-------------------------------------------------------------------------------
# vers-includes
#
$(TARGDIR)/vers-includes: $(addsuffix .vers.h,$(EXT_TOOLS))

.PHONY: $(TARGDIR)/vers-includes

#-------------------------------------------------------------------------------
# clean
#
clean: stdclean

.PHONY: clean

#-------------------------------------------------------------------------------
# tag
#
tag: \
	$(addsuffix _tag,$(ALL_TOOLS))

.PHONY: tag $(addsuffix _tag,$(ALL_TOOLS))


#----------------------------------------------------------------
# kar
#

KAR_SRC = \
	kar

KAR_OBJ = \
	$(addsuffix .$(OBJX),$(KAR_SRC))

KAR_LIB = \
	-skapp \
	-lvfs \
	-lkfg \
	-lkrypto \
	-lkfs \
	-lkproc \
	-lklib \
	-lm

$(BINDIR)/kar: $(KAR_OBJ)
	$(LD) --exe --vers $(SRCDIR) -o $@ $^ $(KAR_LIB)

kar_tag:
	@ $(TOP)/build/tag-module.sh $(MODULE) kar $(KAR_OBJ)

#----------------------------------------------------------------
# sra-kar
#

SRA_KAR_SRC = \
	sra-kar

SRA_KAR_OBJ = \
	$(addsuffix .$(OBJX),$(SRA_KAR_SRC))

SRA_KAR_LIB = \
	-skapp \
	-lsradb \
	-lvdb \
	-lkdb \
	-lvfs \
	-lkfg \
	-lkrypto \
	-lkfs \
	-lkproc \
	-lklib \
	-lm

$(BINDIR)/sra-kar: $(SRA_KAR_OBJ)
	$(LD) --exe --vers $(SRCDIR) -o $@ $^ $(SRA_KAR_LIB)

sra-kar_tag:
	@ $(TOP)/build/tag-module.sh $(MODULE) sra-kar $(SRA_KAR_OBJ)


