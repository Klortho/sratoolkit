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
MODULE = libs/axf

MOD_LIBS = \
	libaxf

WMOD_LIBS = \
	libwaxf

ALL_LIBS = \
	$(MOD_LIBS) \
	$(WMOD_LIBS)

include $(TOP)/build/Makefile.env

#-------------------------------------------------------------------------------
# outer targets
#
all std: makedirs
	@ $(MAKE_CMD) $(TARGDIR)/std

$(ALL_LIBS): makedirs
	@ $(MAKE_CMD) $(TARGDIR)/$@

.PHONY: all std $(ALL_LIBS)

#-------------------------------------------------------------------------------
# std
#
$(TARGDIR)/std: \
	$(addprefix $(TARGDIR)/,$(ALL_LIBS))

.PHONY: $(TARGDIR)/all $(TARGDIR)/std

#-------------------------------------------------------------------------------
# clean
#
clean: stdclean

.PHONY: clean

#-------------------------------------------------------------------------------
# alignment transform library
#
$(TARGDIR)/libaxf: $(addprefix $(TARGDIR)/libaxf.,$(MODEXT))

$(TARGDIR)/libaxf.$(SHLX): $(MODDIR)/libaxf.$(SHLX)

AXF_SRC = \
	ref-tbl-sub-select \
	ref-restore-read \
	align-restore-read \
	raw-restore-read \
	raw-restore-qual \
	seq-restore-read \
	seq-construct-read \
	cigar \
	project_read_from_sequence \
	not-my-row \
	template-len \
	get-sam-flags \
	align-ref-pos \
	align-ref-name \
	align-ref-seq-id \
	align-local_ref_id \
	align-local_ref_start \
	generate-mismatch-qual \
	mismatch-restore-qual \
	ref-preserve_qual \
	ref-tbl \
	make-cmp-read_desc \
	get_mate_align_ids

AXF_OBJ = \
	$(addsuffix .$(LOBX),$(AXF_SRC))

AXF_LIB = \
	-lalign-reader \
	-dvdb \
	-dkdb \
	-dklib \
	-dm \
	-dz

$(MODDIR)/libaxf.$(SHLX): $(AXF_OBJ)
	$(LD) --dlib --vers $(SRCDIR) -o $@ $^ $(AXF_LIB)

$(TARGDIR)/libaxf.$(LIBX): $(ILIBDIR)/libaxf.$(LIBX)

$(ILIBDIR)/libaxf.$(LIBX): $(AXF_OBJ)
	$(LD) --slib -o $@ $^ $(AXF_LIB)


#-------------------------------------------------------------------------------
# alignment transform update library
#
$(TARGDIR)/libwaxf: $(addprefix $(TARGDIR)/libwaxf.,$(MODEXT))

$(TARGDIR)/libwaxf.$(SHLX): $(WMODDIR)/libwaxf.$(SHLX)

WAXF_SRC = \
	$(AXF_SRC) \
	refseq-stats

WAXF_OBJ = \
	$(addsuffix .$(LOBX),$(WAXF_SRC))

WAXF_LIB = \
	-lalign-reader \
	-dwvdb \
	-dwkdb \
	-lkfg \
	-dklib \
	-dm \
	-dz

$(WMODDIR)/libwaxf.$(SHLX): $(WAXF_OBJ)
	$(LD) --dlib --vers $(SRCDIR) -o $@ $^ $(WAXF_LIB)

$(TARGDIR)/libwaxf.$(LIBX): $(ILIBDIR)/libwaxf.$(LIBX)

$(ILIBDIR)/libwaxf.$(LIBX): $(WAXF_OBJ)
	$(LD) --slib -o $@ $^ $(WAXF_LIB)
