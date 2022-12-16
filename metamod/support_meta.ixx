export module support_meta;

import <cstring>;

export import eiface;

export void do_exit(int exitval);

//use pointer to avoid inlining of strcmp
export inline int mm_strcmp(const char *s1, const char *s2) {
#if 0
	int (*__strcmp)(const char *, const char *) = &strcmp;
	return((*__strcmp)(s1, s2));
#else
	return(strcmp(s1, s2));
#endif
}

//use pointer to avoid inlining of strncmp
export inline int mm_strncmp(const char *s1, const char *s2, size_t n) {
#if 0
	int (*__strncmp)(const char *, const char *, size_t) = &strncmp;
	return((*__strncmp)(s1, s2, n));
#else
	return(strncmp(s1, s2, n));
#endif
}

// Unlike snprintf(), strncpy() doesn't necessarily null-terminate the
// target.  It appears the former function reasonably considers the given
// size to be "max size of target string" (including the null-terminator),
// whereas strncpy() strangely considers the given size to be "total number
// of bytes to copy".  Note strncpy() _always_ writes n bytes, whereas
// snprintf() writes a _max_ of n bytes (incl the NULL).  If strncpy()
// needs to write extra bytes to reach n, it uses NULLs, so the target
// _can_ be null-terminated, but only if the source string would have fit
// anyway -  in which case why not just use strcpy() instead?
//
// Thus, it appears strncpy() is not only unsafe, it's also inefficient,
// and seemingly no better than plain strcpy() anyway.
//
// With this logic, strncpy() doesn't appear to be much of a "str" function
// at all, IMHO.
//
// Strncat works better, although it considers the given size to be "number
// of bytes to append", and doesn't include the null-terminator in that
// count.  Thus, we can use it for what we want to do, by setting the
// target to zero-length (NULL in first byte), and copying n-1 bytes
// (leaving room for the null-termiator).
//
// Why does it have to be soo haaard...

// Also note, some kind of wrapper is necessary to group the two
// statements into one, for use in situations like non-braced else
// statements.

// Technique 1: use "do..while":
#if 0
#define STRNCPY(dst, src, size) \
	do { strcpy(dst, "\0"); strncat(dst, src, size-1); } while(0)
#endif

// Technique 2: use parens and commas:
#if 0
#define STRNCPY(dst, src, size) \
	(strcpy(dst, "\0"), strncat(dst, src, size-1))
#endif

// Technique 3: use inline
export inline char *STRNCPY(char *dst, const char *src, int size) {
	return(strncat(&(*dst = 0), src, size - 1));
}

// Renamed string functions to be clearer.
export inline int strmatch(const char *s1, const char *s2)
{
	[[likely]]
	if (s1 && s2)
		return(!mm_strcmp(s1, s2));
	else
		return(0);
}
export inline int strnmatch(const char *s1, const char *s2, size_t n)
{
	[[likely]]
	if (s1 && s2)
		return(!mm_strncmp(s1, s2, n));
	else
		return(0);
}
export inline int strcasematch(const char *s1, const char *s2)
{
	[[likely]]
	if (s1 && s2)
		return(!_stricmp(s1, s2));
	else
		return(0);
}
export inline int strncasematch(const char *s1, const char *s2, size_t n)
{
	[[likely]]
	if (s1 && s2)
		return(!_strnicmp(s1, s2, n));
	else
		return(0);
}

export inline int old_valid_file(char *path)
{
	char *cp;
	int len, ret;
	cp = (char *)g_engfuncs.pfnLoadFileForMe(path, &len);
	if (cp && len)
		ret = 1;
	else
		ret = 0;
	g_engfuncs.pfnFreeFile(cp);
	return(ret);
}
export extern "C++" int valid_gamedir_file(const char *path);
export extern "C++" char *full_gamedir_path(const char *path, char *fullpath);

// Turn a variable/function name into the corresponding string, optionally
// stripping off the leading "len" characters.  Useful for things like
// turning 'pfnClientCommand' into "ClientCommand" so we don't have to
// specify strings used for all the debugging/log messages.
#define STRINGIZE(name, len)		#name+len


// Max description length for plugins.ini and other places.
export inline constexpr auto MAX_DESC_LEN = 256;


// For various character string buffers.
export inline constexpr auto MAX_STRBUF_LEN = 1024;


// Smallest of two
#define MIN(x, y) (((x)<(y))?(x):(y))


// Greatest of two
#define MAX(x, y) (((x)>(y))?(x):(y))
