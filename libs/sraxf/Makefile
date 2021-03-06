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
MODULE = libs/sraxf

MOD_LIBS = \
	libsraxf

WMOD_LIBS = \
	libwsraxf

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
# sra transform library
#
$(TARGDIR)/libsraxf: $(addprefix $(TARGDIR)/libsraxf.,$(MODEXT))

$(TARGDIR)/libsraxf.$(SHLX): $(MODDIR)/libsraxf.$(SHLX)

SRAXF_SRC = \
	untyped \
	v0-decompress-init \
	v0-decompress \
	v0-funcs \
	bio-start \
	dynamic-454-read-descriptor \
	format-spot-name \
	extract-name_coord \
	tokenize-spot_name-454 \
	tokenize-spot_name-illumina \
	tokenize-spot_name-abi \
	tokenize-spot_name-helicos \
	tokenize-spot_name-ion-torrent \
	color-from-dna \
	dna-from-color \
	spot-desc \
	read-desc \
	rotate \
	swap \
	denormalize \
	normalize \
	qual4_decode \
	read-seg-from-readn \
	rewrite-spot-name \
	make-position \
	process-position \
	extract-coordinates \
	fpcodec \
	index_lookup \
	varloc

SRAXF_OBJ = \
	$(addsuffix .$(LOBX),$(SRAXF_SRC))

SRAXF_LIB = \
	-dksrch \
	-dvdb \
	-dkdb \
	-dklib \
	-dm \
	-dz

$(MODDIR)/libsraxf.$(SHLX): $(SRAXF_OBJ)
	$(LD) --dlib --vers $(SRCDIR) -o $@ $^ $(SRAXF_LIB)

$(TARGDIR)/libsraxf.$(LIBX): $(ILIBDIR)/libsraxf.$(LIBX)

$(ILIBDIR)/libsraxf.$(LIBX): $(SRAXF_OBJ)
	$(LD) --slib -o $@ $^ $(SRAXF_LIB)


#-------------------------------------------------------------------------------
# sra transform update library
#
$(TARGDIR)/libwsraxf: $(addprefix $(TARGDIR)/libwsraxf.,$(MODEXT))

$(TARGDIR)/libwsraxf.$(SHLX): $(WMODDIR)/libwsraxf.$(SHLX)

WSRAXF_SRC = \
	$(SRAXF_SRC) \
	extract-name_fmt \
	extract-spot_name \
	stats \
	stats_quality \
	qual4_encode

WSRAXF_OBJ = \
	$(addsuffix .$(LOBX),$(WSRAXF_SRC))

WSRAXF_LIB = \
	-dwvdb \
	-dwkdb \
	-dksrch \
	-dklib \
	-dm \
	-dz

$(WMODDIR)/libwsraxf.$(SHLX): $(WSRAXF_OBJ)
	$(LD) --dlib --vers $(SRCDIR) -o $@ $^ $(WSRAXF_LIB)

$(TARGDIR)/libwsraxf.$(LIBX): $(ILIBDIR)/libwsraxf.$(LIBX)

$(ILIBDIR)/libwsraxf.$(LIBX): $(WSRAXF_OBJ)
	$(LD) --slib -o $@ $^ $(WSRAXF_LIB)
