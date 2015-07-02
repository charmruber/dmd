#ifndef ROOT_H
#define ROOT_H

#include <stdlib.h>
#include <stdarg.h>

#endif

#include "dchar.h"

char *wchar2ascii(wchar_t *);
int wcharIsAscii(wchar_t *);
char *wchar2ascii(wchar_t *, unsigned len);
