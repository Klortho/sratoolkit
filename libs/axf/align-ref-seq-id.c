/*===========================================================================
 *
 *                            PUBLIC DOMAIN NOTICE
 *               National Center for Biotechnology Information
 *
 *  This software/database is a "United States Government Work" under the
 *  terms of the United States Copyright Act.  It was written as part of
 *  the author's official duties as a United States Government employee and
 *  thus cannot be copyrighted.  This software/database is freely available
 *  to the public for use. The National Library of Medicine and the U.S.
 *  Government have not placed any restriction on its use or reproduction.
 *
 *  Although all reasonable efforts have been taken to ensure the accuracy
 *  and reliability of the software and data, the NLM and the U.S.
 *  Government do not and cannot warrant the performance or results that
 *  may be obtained by using this software or data. The NLM and the U.S.
 *  Government disclaim all warranties, express or implied, including
 *  warranties of performance, merchantability or fitness for any particular
 *  purpose.
 *
 *  Please cite the author in any work or product based on this material.
 *
 * ===========================================================================
 *
 */
#include <vdb/extern.h>

#include <vdb/xform.h>
#include <vdb/database.h>
#include <vdb/table.h>
#include <vdb/cursor.h>
#include <vdb/vdb-priv.h>
#include <insdc/insdc.h>
#include <klib/data-buffer.h>
#include <klib/rc.h>
#include <sysalloc.h>

#include <bitstr.h>

#include "ref-tbl.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct RefSeqID RefSeqID;
struct RefSeqID
{
    const VCursor *curs;
    uint32_t seqID_idx;
};

static
void CC RefSeqIDWhack ( void *obj )
{
    RefSeqID * self = obj;
    if ( self != NULL )
    {
        VCursorRelease ( self -> curs );
        free ( self );
    }
}

static
rc_t RefSeqIDMake ( RefSeqID **objp, const VTable *tbl )
{
    rc_t rc;

    /* create the object */
    RefSeqID *obj = malloc ( sizeof * obj );
    if ( obj == NULL ) {
        rc = RC ( rcXF, rcFunction, rcConstructing, rcMemory, rcExhausted );
    } else {
        /* open the reference table */
        const VTable *reftbl;
        if( (rc = AlignRefTable(tbl, &reftbl)) == 0 ) {
            /* create a cursor */
            rc = VTableCreateCachedCursorRead(reftbl, &obj->curs, 2*1024*1024);
            VTableRelease(reftbl);
            if( rc == 0 ) {
                /* add columns to cursor */
                if( (rc = VCursorAddColumn(obj->curs, &obj->seqID_idx, "SEQ_ID")) == 0 ) {
                    rc = VCursorOpen(obj->curs);
                }
                if( GetRCObject(rc) == rcColumn && GetRCState(rc) == rcNotFound ) {
                    if( (rc = VCursorAddColumn(obj->curs, &obj->seqID_idx, "REF_SEQ_ID")) == 0 ) {
                        rc = VCursorOpen(obj->curs);
                    }
                }
                if( rc == 0 ) {
                    *objp = obj;
                    return 0;
                }
                VCursorRelease ( obj -> curs );
            }
        }
        free ( obj );
    }
    return rc;
}

enum align_ref_name_args {
    REF_ID
};

/*
 function ascii NCBI:align:ref_seq_id ( I64 ref_id );
*/
static
rc_t CC align_ref_seq_id ( void *data, const VXformInfo *info,
    int64_t row_id, VRowResult *rslt, uint32_t argc, const VRowData argv[] )
{
    rc_t rc;
    RefSeqID const *self = (void const *)data;
    char const *name = NULL;
    uint32_t name_len;

    /* get start and length of reference segment */
    int64_t const *ref_id = argv[REF_ID].u.data.base;

    assert(argv[REF_ID].u.data.elem_bits == sizeof(*ref_id) * 8);

    if( self->curs == NULL || argv[REF_ID].u.data.elem_count == 0 ) {
        rslt->elem_count = 0;
        return 0;
    }
    ref_id += argv[REF_ID].u.data.first_elem;
    
    rc = VCursorCellDataDirect(self->curs, ref_id[0], self->seqID_idx, NULL, (void const **)&name, NULL, &name_len);
    if (GetRCState(rc) == rcNotFound && GetRCObject(rc) == rcRow) {
        name = "";
        name_len = 0;
    } else if( rc != 0 ) {
        return rc;
    }
    rc = KDataBufferCast(rslt->data, rslt->data, sizeof(name[0]) * 8, true);
    if (rc) return rc;

    rc = KDataBufferResize(rslt->data, name_len);
    if (rc) return rc;
    
    memcpy(rslt->data->base, name, sizeof(name[0]) * name_len);
    rslt->elem_count = name_len;
    rslt->elem_bits = sizeof(name[0]) * 8;
    return rc;
}

VTRANSFACT_IMPL ( NCBI_align_ref_seq_id, 1, 0, 0 ) ( const void *self, const VXfactInfo *info,
    VFuncDesc *rslt, const VFactoryParams *cp, const VFunctionParams *dp )
{
    RefSeqID *fself;
    rc_t rc = RefSeqIDMake ( & fself, info -> tbl );
    if ( rc == 0 )
    {
        rslt -> self = fself;
        rslt -> whack = RefSeqIDWhack;
        rslt -> u . rf = align_ref_seq_id;
        rslt -> variant = vftRow;
    }

    return rc;
}
