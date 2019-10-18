/****************************************************************
 *
 * Copyright (C) 2014,2018 Alessandro Pignotti <alessandro@leaningtech.com>
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

#include <errno.h>

extern int __builtin_cheerp_grow_memory(int);

// HACK: The value of this variables will be rewritten to the correct heap start
// and end by the compiler backend
__attribute__((cheerp_asmjs)) char* volatile _heapStart = (char*)0xdeadbeef;
__attribute__((cheerp_asmjs)) char* volatile _heapEnd = (char*)0xdeadbeef;

__attribute__((cheerp_asmjs)) char* _heapCur = 0;

static void setErrno(int e)
{
	errno = e;
}
__attribute__((cheerp_asmjs)) void* sbrk(int nbytes)
{
	if (_heapCur == 0)
		_heapCur = _heapStart;
	if (nbytes == 0)
		return _heapEnd;
	char* prevCur = _heapCur;
	if (_heapCur + nbytes >= _heapEnd)
	{

		int res = __builtin_cheerp_grow_memory(nbytes);
		if (res==-1) {
			setErrno(ENOMEM);
			return (void*)(-1);
		}
		_heapEnd += res;
	}
	_heapCur += nbytes;
	return prevCur;
}

__attribute__((cheerp_asmjs)) void* _sbrk_r(void* reent, int nbytes)
{
	(void)reent;
	return sbrk(nbytes);
}
