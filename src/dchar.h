#ifndef DCHAR_H
#define DCHAR_H

#if _MSC_VER
    #pragma warning (disable : 4514)
#endif

#undef TEXT

#if UNICODE

#include <string.h>
#include <wchar.h>

typedef wchar_t dchar;
#define TEXT(x)

#define Dchar_mbmax        1

struct Dchar {
    static dchar *inc(dchar *p) { return p + 1; }
    static dchar *dec(dchar *pstart, dchar *p) { (void)pstart; return p - 1; }
    static int len(const dchar *p) { return wcslen(p); }
    static dchar get(dchar *p) { return *p }
    static dchar getprev(dchar *pstart, dchar *p) { (void)pstart; return p[-1]; }
    static dchar *put(dchar *p, dchar c) { *p = c; return p + 1; }
    static int cmp(dchar *s1, dchar *s2) {
#if __DMC__
        if (!*s1 && !s2) {
            return 0;
        }
#endif
        return wcscmp(s1, s2);
#if 0
        return (*s1 == *s2) ? wcscmp(s1, s2) : ((int)*s1 - (int)*s2);
#endif
    }
    static int memcmp(const dchar *s1, const dchar *s2, int nchars) {
        return ::memchmp(s1, s2, nchars * sizeof(dchar));
    }
    static isDigit(dchar c) { return '0' <= c && c <= '9' }
    static isAlpha(dchar c) { return iswalpha(c); }
    static
}
