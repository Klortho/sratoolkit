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
MODULE = libs/vdb

INT_LIBS = \

EXT_LIBS = \
	libvdb \
	libwvdb

ALL_LIBS = \
	$(INT_LIBS) \
	$(EXT_LIBS)

include $(TOP)/build/Makefile.env

#-------------------------------------------------------------------------------
# outer targets
#
all std: vers-includes
	@ $(MAKE_CMD) $(TARGDIR)/std

$(INT_LIBS): vers-includes
	@ $(MAKE_CMD) $(ILIBDIR)/$@

$(EXT_LIBS): vers-includes
	@ $(MAKE_CMD) $(LIBDIR)/$@

.PHONY: all std $(ALL_LIBS)

#-------------------------------------------------------------------------------
# std
#
$(TARGDIR)/std: \
	$(addprefix $(ILIBDIR)/,$(INT_LIBS)) \
	$(addprefix $(LIBDIR)/,$(EXT_LIBS))

.PHONY: $(TARGDIR)/all $(TARGDIR)/std

#-------------------------------------------------------------------------------
# vers-includes
#
$(TARGDIR)/vers-includes: $(addsuffix .vers.h,$(EXT_LIBS))

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
	$(addsuffix _tag,$(ALL_LIBS))

.PHONY: tag $(addsuffix _tag,$(ALL_LIBS))

#-------------------------------------------------------------------------------
# virtual db library
#
$(LIBDIR)/libvdb: $(addprefix $(LIBDIR)/libvdb.,$(LIBEXT))

VDBCMN_SRC = \
	dbmgr-cmn \
	schema-tok \
	schema-parse \
	schema-type \
	schema-func \
	schema-prod \
	schema-expr \
	schema-eval \
	schema-tbl \
	schema-db \
	schema-dump \
	schema-int \
	schema \
	linker-int \
	linker-cmn \
	database-cmn \
	database-depend \
	database-load \
	table-cmn \
	table-load \
	cursor-cmn \
	column-cmn \
	prod-cmn \
	prod-expr \
	prod-func \
	phys-cmn \
	phys-load \
	blob \
	blob-headers \
	page-map \
	row-id \
	row-len \
	fixed-row-len \
	merge \
	split \
	compare \
	meta-read \
	meta-value \
	meta-attr-read \
	cast \
	range-validate \
	parameter-read \
	redimension \
	index_project \
	index_lookup \
	transpose \
	delta_average \
	report-vdb

VDB_SRC = \
	$(VDBCMN_SRC) \
	dbmgr \
	linker \
	database \
	table \
	cursor \
	column \
	prod \
	phys

VDB_OBJ = \
	$(addsuffix .$(LOBX),$(VDB_SRC))

VDB_LIB = \
	-dkdb \
	-dkfg \
	-dkfs \
	-dklib \
	-dz

$(LIBDIR)/libvdb.$(SHLX): $(VDB_OBJ)
	$(LD) --dlib --vers $(SRCDIR) -o $@ $^ $(VDB_LIB)

$(LIBDIR)/libvdb.$(LIBX): $(VDB_OBJ)
	$(LD) --slib --vers $(SRCDIR) -o $@ $^ $(VDB_LIB)

libvdb_tag: $(VDB_TAGS)
	@ $(TOP)/build/tag-module.sh $(MODULE) libvdb $(VDB_OBJ)

#-------------------------------------------------------------------------------
# update version
#
$(LIBDIR)/libwvdb: $(addprefix $(LIBDIR)/libwvdb.,$(LIBEXT))

WVDB_SRC = \
	$(VDBCMN_SRC) \
	wdbmgr \
	wlinker \
	wdatabase \
	wtable \
	wcursor \
	wcolumn \
	wprod \
	wphys \
	meta-write \
	meta-attr-write \
	meta-append \
	index_insert

WVDB_OBJ = \
	$(addsuffix .$(LOBX),$(WVDB_SRC))

WVDB_LIB = \
	-dwkdb \
	-dkfg \
	-dkfs \
	-dkproc \
	-dklib \
	-dz

$(LIBDIR)/libwvdb.$(SHLX): $(WVDB_OBJ)
	$(LD) --dlib --vers $(SRCDIR) -o $@ $^ $(WVDB_LIB)

$(LIBDIR)/libwvdb.$(LIBX): $(WVDB_OBJ)
	$(LD) --slib --vers $(SRCDIR) -o $@ $^ $(WVDB_LIB)

libwvdb_tag: $(WVDB_TAGS)
	@ $(TOP)/build/tag-module.sh $(MODULE) libwvdb $(WVDB_OBJ)
