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
MODULE = tools/vdb-dump

include $(TOP)/build/Makefile.env

INT_TOOLS = \

EXT_TOOLS = \
	vdb-dump

ALL_TOOLS = \
	$(INT_TOOLS) \
	$(EXT_TOOLS)

#-------------------------------------------------------------------------------
# outer targets
#
all std: vers-includes
	@ $(MAKE_CMD) $(TARGDIR)/$@

$(ALL_TOOLS): vers-includes
	@ $(MAKE_CMD) $(BINDIR)/$@

.PHONY: all std $(ALL_TOOLS)

#-------------------------------------------------------------------------------
# all
#
$(TARGDIR)/all: \
	$(addprefix $(BINDIR)/,$(ALL_TOOLS))

.PHONY: $(TARGDIR)/all

#-------------------------------------------------------------------------------
# std
#
$(TARGDIR)/std: \
	$(addprefix $(BINDIR)/,$(EXT_TOOLS))

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
# vdb-dump
#  vdb dump tool
#
VDB_DUMP_SRC = \
	vdb-dump-num-gen \
	vdb-dump-context \
	vdb-dump-coldefs \
	vdb-dump-tools \
	vdb-dump-str \
	vdb-dump-helper \
	vdb-dump-filter \
	vdb-dump-formats \
	vdb-dump

VDB_DUMP_OBJ = \
	$(addsuffix .$(OBJX),$(VDB_DUMP_SRC))

VDB_DUMP_LIB = \
	-ssraschema \
	-dalign-reader \
	$(READONLY_SCHEMA_LIBS) \
	-lksrch \
	-lvdb \
	-lkdb \
	-lvfs \
	-lkrypto \
	-lkapp \
	-lkfg \
	-lkfs \
	-lkproc \
	-lklib \
	-lm

$(BINDIR)/vdb-dump: $(VDB_DUMP_OBJ)
	$(LD) --exe --vers $(SRCDIR) -o $@ $^ $(VDB_DUMP_LIB)
