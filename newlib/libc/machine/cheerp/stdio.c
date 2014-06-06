/****************************************************************
 *
 * Copyright (C) 2013 Alessandro Pignotti <alessandro@leaningtech.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 ***************************************************************/

#include <stdio.h>
#include <malloc.h>
#include "clientbridge.h"

FILE *
_MACDEFUN (__sfp, (d),
	struct _reent *d)
{
  FILE *fp;
  int n;
  struct _glue *g;

  fp=(FILE*)_malloc_r(d, sizeof(FILE));

  fp->_file = -1;		/* no file */
  fp->_flags = 1;		/* reserve this slot; caller sets real flags */
  fp->_flags2 = 0;
  fp->_p = NULL;		/* no current pointer */
  fp->_w = 0;			/* nothing to read or write */
  fp->_r = 0;
  fp->_bf._base = NULL;		/* no buffer */
  fp->_bf._size = 0;
  fp->_lbfsize = 0;		/* not line buffered */
  __builtin_memset (&fp->_mbstate, 0, sizeof (_mbstate_t));
  /* fp->_cookie = <any>; */	/* caller sets cookie, _read/_write etc */
  fp->_ub._base = NULL;		/* no ungetc buffer */
  fp->_ub._size = 0;
  fp->_lb._base = NULL;		/* no line buffer */
  fp->_lb._size = 0;

  return fp;
}

static _VOID
_FUN(std, (ptr, flags, file, data),
            FILE *ptr _AND
            int flags _AND
            int file  _AND
            struct _reent *data)
{
  ptr->_p = 0;
  ptr->_r = 0;
  ptr->_w = 0;
  ptr->_flags = flags;
  ptr->_flags2 = 0;
  ptr->_file = file;
  ptr->_bf._base = 0;
  ptr->_bf._size = 0;
  ptr->_lbfsize = 0;
  __builtin_memset (&ptr->_mbstate, 0, sizeof (_mbstate_t));
  ptr->_cookie = ptr;
#ifndef __LARGE64_FILES
  ptr->_write = __cheerpwrite;
#endif /* __LARGE64_FILES */

#ifdef __SCLE
  if (__stextmode (ptr->_file))
    ptr->_flags |= __SCLE;
#endif
}

_VOID
_MACDEFUN(__sinit, (s),
       struct _reent *s)
{
  __sinit_lock_acquire ();

  if (s->__sdidinit)
    {
      __sinit_lock_release ();
      return;
    }

  /* make sure we clean up on exit */
  //s->__cleanup = _cleanup_r;	/* conservative */

  s->__sglue._next = NULL;
  s->__sglue._niobs = 0;
  s->__sglue._iobs = NULL;
  /* Avoid infinite recursion when calling __sfp  for _GLOBAL_REENT.  The
     problem is that __sfp checks for _GLOBAL_REENT->__sdidinit and calls
     __sinit if it's 0. */
  if (s == _GLOBAL_REENT)
    s->__sdidinit = 1;
  s->_stdin = __sfp(s);
  s->_stdout = __sfp(s);
  s->_stderr = __sfp(s);

  std (s->_stdin,  __SRD, -1, s);

  /* On platforms that have true file system I/O, we can verify
     whether stdout is an interactive terminal or not, as part of
     __smakebuf on first use of the stream.  For all other platforms,
     we will default to line buffered mode here.  Technically, POSIX
     requires both stdin and stdout to be line-buffered, but tradition
     leaves stdin alone on systems without fcntl.  */
  std (s->_stdout, __SWR | __SLBF, -2, s);

  std (s->_stderr, __SWR | __SLBF, -2, s);

  s->__sdidinit = 1;

  __sinit_lock_release ();
}
