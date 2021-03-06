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

#ifndef _h_kdb_priv_
#define _h_kdb_priv_

#ifndef _h_kdb_manager_
#include <kdb/manager.h>
#endif

#ifndef _h_kdb_manager_
#include <kdb/manager.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*--------------------------------------------------------------------------
 * forwards
 */
struct BSTree;
struct BSTNode;


/*--------------------------------------------------------------------------
 * KDB utility
 */


/* PathType
 *  checks type of path
 */
int KDBPathType ( const KDirectory *dir, bool *zombies, const char *path );

/* OpenPathType
 * Opens a path if it is of the specified type.  Even if it is an archive file
 * instead of a directory.
 *
 * if dpdir is NULL it will not return with an open Directory but it will have
 * checked that the type requested is the type present even if in an archive.
 *
 * if realpathtype is not NULL the found type will be returned regardless
 * of a match to request path type.
 *
 * the return will be zero only if the path does point to a directory or
 * archive that is of the requested type.  An archive will have been opened
 * but reshut if dpdir is NULL.
 */ 
rc_t KDBOpenPathTypeRead ( const KDirectory * dir, const char * path, 
    const KDirectory ** dpdir, int pathtype, int * realpathtype, bool try_srapath );

/* Writable
 *  examines a directory structure for any "lock" files
 *  examines a file for ( any ) write permission
 */
bool KDBIsLocked ( const KDirectory *dir, const char *path );
rc_t KDBWritable ( const KDirectory *dir, const char *path );

/* Lock
 *  performs directory locking
 */
rc_t KDBLockDir ( KDirectory *dir, const char *path );
rc_t KDBLockFile ( KDirectory *dir, const char *path );

/* Unlock
 *  performs directory unlocking
 */
rc_t KDBUnlockDir ( KDirectory *dir, const char *path );
rc_t KDBUnlockFile ( KDirectory *dir, const char *path );

/* GetObjModDate
 *  extract mod date from a path
 */
rc_t KDBGetObjModDate ( const KDirectory *dir, KTime_t *mtime );

/* GetPathModDate
 *  extract mod date from a path
 */
rc_t KDBVGetPathModDate ( const KDirectory *dir,
    KTime_t *mtime, const char *path, va_list args );

/* GetNamespaceString
 *  return a static const reference to a string representing 
 *  a namespace for the given kpt<database> type in namespace
 */
const char * KDBGetNamespaceString ( int namespace );

/* VMakeSubPath
 *  adds a namespace to path spec
 */
rc_t KDBVMakeSubPath ( const KDirectory *dir,
    char *subpath, size_t subpath_max, const char *ns,
    uint32_t ns_size, const char *path, va_list args );

/* VDrop
 */
rc_t KDBMgrVDrop ( KDirectory * dir, const KDBManager * mgr, uint32_t obj_type,
                   const char * path, va_list args );
rc_t KDBVDrop ( KDirectory *dir, const KDBManager * mgr,
    uint32_t type, const char *name, va_list args );

/* Rename
 */
rc_t KDBRename ( KDirectory *dir, KDBManager *mgr,
                 uint32_t type, bool force, const char *from, const char *to );

/* Alias
 */
rc_t KDBAlias ( KDirectory *dir, uint32_t type,
    const char *targ, const char *alias );


#ifdef __cplusplus
}
#endif

#endif /* _h_kdb_priv_ */
