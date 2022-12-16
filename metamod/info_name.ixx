export module info_name;

//
// Original vers_meta.h
//

#define _VMETA_VERSION "1.21"
#define _VPATCH_IVERSION 38
#define _VPATCH_VERSION "38"
#define _VPATCH_COPYRIGHT_YEAR	"2018"

#define _VVERSION	_VMETA_VERSION "p" _VPATCH_VERSION

export inline constexpr char OPT_TYPE[] = "default";

export inline constexpr char VDATE[] = "2018/02/11";
export inline constexpr char VPATCH_COPYRIGHT_YEAR[] = _VPATCH_COPYRIGHT_YEAR;
export inline constexpr char VMETA_VERSION[] = _VMETA_VERSION;

export inline constexpr char VPATCH_NAME[] = "Metamod-P (mm-p)";
export inline constexpr char VPATCH_IVERSION = _VPATCH_IVERSION;
export inline constexpr char VPATCH_VERSION[] = _VPATCH_VERSION;
export inline constexpr char VPATCH_AUTHOR[] = "Jussi Kivilinna";
export inline constexpr char VPATCH_WEBSITE[] = "http://metamod-p.sourceforge.net/";

export inline constexpr char VVERSION[] = _VVERSION;
#define RC_VERS_DWORD		1,21,0,VPATCH_IVERSION	// Version Windows DLL Resources in res_meta.rc

//
// Original info_name.h
//

#define _COPYRIGHT_YEAR "2013"

#define _VNAME			"Metamod"
#define _VURL			"http://www.metamod.org/"

export inline constexpr char VNAME[] = _VNAME;
export inline constexpr char VAUTHOR[] = "Will Day";
export inline constexpr char VURL[] = _VURL;

export inline constexpr char COPYRIGHT_YEAR[] = _COPYRIGHT_YEAR;

// Various strings for the Windows DLL Resources in res_meta.rc
export inline constexpr char RC_COMMENTS[] = "Metamod-P is enhanced version of Metamod. Metamod allows running multiple mod-like plugin DLLs, to add functionality or change the behavior of the running HLDS game mod.  See " _VURL;
export inline constexpr char RC_DESC[] = "Metamod-P Half-Life MOD DLL";
export inline constexpr char RC_FILENAME[] = "METAMOD.DLL";
export inline constexpr char RC_INTERNAL[] = "METAMOD-P";
export inline constexpr char RC_COPYRIGHT[] = "Copyright© 2001-" _COPYRIGHT_YEAR " Will Day; 2004-" _VPATCH_COPYRIGHT_YEAR " Jussi Kivilinna; GPL licensed";
export inline constexpr char RC_LICENSE[] = "Licensed under the GNU General Public License";

//
// vdata.cpp
//

export inline constexpr char COMPILE_TIME[] = __DATE__ ", " __TIME__;

#ifndef COMPILE_TZ
export inline constexpr char COMPILE_TZ[] = "EET";
#endif

export inline constexpr char COMPILE_TZONE[sizeof(COMPILE_TZ)] = COMPILE_TZ;

// Include a string for /usr/bin/ident.

export inline constexpr char vstring[] = "\n$Pg: " _VNAME " -- " _VVERSION " | " __DATE__ " - " __TIME__ " $\n";
