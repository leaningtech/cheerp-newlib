/****************************************************************
 *
 * Copyright (C) 2014 Alessandro Pignotti <alessandro@leaningtech.com>
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

#ifdef __ASMJS__
// HACK: The value of this variable will be rewritten to the correct heap start
// by the compiler backend
char* volatile _heapStart = (char*)0xdeadbeef;

void* sbrk(int nbytes)
{
	static char* heapEnd = 0;
	if (heapEnd == 0)
		heapEnd = _heapStart;
	char* prev_end = heapEnd;
	heapEnd += nbytes;
	//TODO: check if we reached end of heap
	return prev_end;
}

void* _sbrk_r(void* reent, int nbytes)
{
	(void)reent;
	return sbrk(nbytes);
}
#else
#include <malloc.h>

void* fakeMallocPtr = 0;

void*
_MACDEFUN(malloc, (s),
       size_t s)
{
	return fakeMallocPtr;
}
#endif
