#ifdef MALLOC_PROVIDED
extern int _dummy_calloc;
#else
/* realloc.c -- a wrapper for realloc_r.  */

#include <_ansi.h>
#include <reent.h>
#ifdef __CHEERP__
#define INTERNAL_NEWLIB
#endif
#include <malloc.h>

#ifndef _REENT_ONLY

_PTR
__attribute__((cheerp_asmjs)) _DEFUN (realloc, (ap, nbytes),
	_PTR ap _AND
	size_t nbytes)
{
  return _realloc_r (NULL, ap, nbytes);
}

#endif
#endif /* MALLOC_PROVIDED */
