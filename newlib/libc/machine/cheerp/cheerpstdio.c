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
#include <sys/stat.h>
#include <errno.h>
#include "clientbridge.h"

_READ_WRITE_RETURN_TYPE
_DEFUN(_write, (fd, buf, n),
       int fd _AND
       const char *buf _AND
       int n)
{
	if (fd!=1 && fd!=2)
		abort();
	return __cheerpwrite(fd, buf, n);
}

_READ_WRITE_RETURN_TYPE
_DEFUN(_read, (fd, buf, n),
       int fd _AND
       const char *buf _AND
       int n)
{
	return -1;
}

__attribute__((weak)) int _close(int fd)
{
	return -1;
}

__attribute__((weak)) off_t _lseek(int fd, off_t offset, int whence)
{
	return -1;
}

__attribute__((weak)) int _stat(const char *pathname, struct stat *buf)
{
	return -1;
}

int _isatty(int fd)
{
  if (fd < 0 || fd > 3)
  {
    return 0;
  }
  return 1;
}

__attribute__((weak)) int _fstat(int fd, struct stat *st)
{
  if (fd >= 0 && fd < 3)
  {
      st->st_mode = S_IFCHR;
      st->st_blksize = 0;
      return 0;
  }
  else
  {
      return -1;
  }
}
