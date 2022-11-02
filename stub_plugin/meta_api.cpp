// vi: set ts=4 sw=4 :
// vim: set tw=75 :

// meta_api.cpp - minimal implementation of metamod's plugin interface

// This is intended to illustrate the (more or less) bare minimum code
// required for a valid metamod plugin, and is targeted at those who want
// to port existing HL/SDK DLL code to run as a metamod plugin.

/*
 * Copyright (c) 2001-2006 Will Day <willday@hpgx.net>
 *
 *    This file is part of Metamod.
 *
 *    Metamod is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    Metamod is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Metamod; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */

import extdll;		// always
import meta_api;	// of course

extern int GetEntityAPI2(DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion) noexcept;
extern int GetEngineFunctions(enginefuncs_t *pengfuncsFromEngine, int *interfaceVersion) noexcept;

// Must provide at least one of these..
inline META_FUNCTIONS gMetaFunctionTable =
{
	nullptr,			// pfnGetEntityAPI				HL SDK; called before game DLL
	nullptr,			// pfnGetEntityAPI_Post			META; called after game DLL
	GetEntityAPI2,		// pfnGetEntityAPI2				HL SDK2; called before game DLL
	nullptr,			// pfnGetEntityAPI2_Post		META; called after game DLL
	nullptr,			// pfnGetNewDLLFunctions		HL SDK2; called before game DLL
	nullptr,			// pfnGetNewDLLFunctions_Post	META; called after game DLL
	GetEngineFunctions,	// pfnGetEngineFunctions		META; called before HL engine
	nullptr,			// pfnGetEngineFunctions_Post	META; called after HL engine
};

// Description of plugin
inline plugin_info_t Plugin_info =
{
	META_INTERFACE_VERSION,	// ifvers
	"minimal stub",	// name
	"1.17",	// version
	"2003/11/15",	// date
	"Will Day <willday@metamod.org>",	// author
	"http://www.metamod.org/",	// url
	"STUB",	// logtag, all caps please
	PT_ANYTIME,	// (when) loadable
	PT_ANYPAUSE,	// (when) unloadable
};

// Metamod requesting info about this plugin:
//  ifvers			(given) interface_version metamod is using
//  pPlugInfo		(requested) struct with info about plugin
//  pMetaUtilFuncs	(given) table of utility functions provided by metamod
int Meta_Query(char * /*ifvers */, plugin_info_t **pPlugInfo, mutil_funcs_t *pMetaUtilFuncs) noexcept
{
	// Give metamod our plugin_info struct
	*pPlugInfo = &Plugin_info;
	// Get metamod utility function table.
	gpMetaUtilFuncs = pMetaUtilFuncs;
	return true;
}

// Metamod attaching plugin to the server.
//  now				(given) current phase, ie during map, during changelevel, or at startup
//  pFunctionTable	(requested) table of function tables this plugin catches
//  pMGlobals		(given) global vars from metamod
//  pGamedllFuncs	(given) copy of function tables from game dll
int Meta_Attach(PLUG_LOADTIME /* now */, META_FUNCTIONS *pFunctionTable, meta_globals_t *pMGlobals, gamedll_funcs_t *pGamedllFuncs) noexcept
{
	if (!pMGlobals)
	{
		//LOG_ERROR(PLID, "Meta_Attach called with null pMGlobals");
		return false;
	}

	gpMetaGlobals = pMGlobals;

	if (!pFunctionTable)
	{
		//LOG_ERROR(PLID, "Meta_Attach called with null pFunctionTable");
		return false;
	}

	memcpy(pFunctionTable, &gMetaFunctionTable, sizeof(META_FUNCTIONS));
	gpGamedllFuncs = pGamedllFuncs;
	return true;
}

// Metamod detaching plugin from the server.
// now		(given) current phase, ie during map, etc
// reason	(given) why detaching (refresh, console unload, forced unload, etc)
int Meta_Detach(PLUG_LOADTIME /* now */, PL_UNLOAD_REASON /* reason */) noexcept
{
	return true;
}
