/*
 * Copyright (c) 2004-2006 Jussi Kivilinna
 *
 *    This file is part of "Metamod All-Mod-Support"-patch for Metamod.
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

//#include <stddef.h>			// offsetof
//#include <extdll.h>
//
//#include "ret_type.h"
//#include "types_meta.h"
//#include "api_info.h"
//#include "api_hook.h"
//#include "mplugin.h"
//#include "metamod.h"
//#include "osdep.h"			//unlikely

import engine_t;
import metamod;

// getting pointer with table index is faster than with if-else
static const void ** api_tables[3] = {
	(const void**)&Engine.funcs,
	(const void**)&GameDLL.funcs.dllapi_table,
	(const void**)&GameDLL.funcs.newapi_table
};

static const void ** api_info_tables[3] = {
	(const void**)&engine_info,
	(const void**)&dllapi_info,
	(const void**)&newapi_info
};

// Safety check for metamod-bot-plugin bugfix.
//  engine_api->pfnRunPlayerMove calls dllapi-functions before it returns.
//  This causes problems with bots running as metamod plugins, because
//  metamod assumed that PublicMetaGlobals is free to be used.
//  With call_count we can fix this by backuping up PublicMetaGlobals if 
//  it's already being used.
static unsigned int call_count = 0;

// get function pointer from api table by function pointer offset
inline void *get_api_function(const void *api_table, unsigned int func_offset) noexcept
{
	return(*(void **)((unsigned long)api_table + func_offset));
}

// get data pointer from api_info table by function offset
inline const api_info_t *get_api_info(enum_api_t api, unsigned int api_info_offset) noexcept
{
	return((const api_info_t *)((unsigned long)api_info_tables[api] + api_info_offset));
}

// simplified 'void' version of main hook function
void main_hook_function_void(unsigned int api_info_offset, enum_api_t api, unsigned int func_offset, const void * packed_args) noexcept
{
	const api_info_t *api_info;
	int i;
	META_RES mres, status, prev_mres;
	MPlugin *iplug;
	void *pfn_routine;
	int loglevel;
	const void *api_table;
	meta_globals_t backup_meta_globals[1];
	
	//passing offset from api wrapper function makes code faster/smaller
	api_info = get_api_info(api, api_info_offset);
	
	//Fix bug with metamod-bot-plugins.
	if (call_count++ > 0)
	{
		//Backup PublicMetaGlobals.
		backup_meta_globals[0] = PublicMetaGlobals;
	}
	
	//Setup
	loglevel=api_info->loglevel;
	mres=MRES_UNSET;
	status=MRES_UNSET;
	prev_mres=MRES_UNSET;
	pfn_routine=nullptr;
	
	//Pre plugin functions
	prev_mres=MRES_UNSET;
	for (i = 0; i < Plugins->endlist; i++)
	{
		iplug = &Plugins->plist[i];

		if (iplug->status != PL_RUNNING)
			continue;

		api_table = iplug->get_api_table(api);
		if (!api_table) {
			//plugin doesn't provide this api table
			continue;
		}

		pfn_routine = get_api_function(api_table, func_offset);
		if (!pfn_routine) {
			//plugin doesn't provide this function
			continue;
		}

		// initialize PublicMetaGlobals
		PublicMetaGlobals.mres = MRES_UNSET;
		PublicMetaGlobals.prev_mres = prev_mres;
		PublicMetaGlobals.status = status;

		// call plugin
		api_info->api_caller(pfn_routine, packed_args);

		// plugin's result code
		mres = PublicMetaGlobals.mres;
		if (mres > status)
			status = mres;

		// save this for successive plugins to see
		prev_mres = mres;
	}
	
	call_count--;
	
	//Api call
	if (status != MRES_SUPERCEDE) {
		//get api table
		api_table = *api_tables[api];

		if (api_table) {
			pfn_routine = get_api_function(api_table, func_offset);
			if (pfn_routine) {
				api_info->api_caller(pfn_routine, packed_args);
			}
			else {
				// don't complain for NULL routines in NEW_DLL_FUNCTIONS
				status = MRES_UNSET;
			}
		}
		else {
			// don't complain for NULL NEW_DLL_FUNCTIONS-table
			status = MRES_UNSET;
		}
	}

	call_count++;
	
	//Post plugin functions
	prev_mres=MRES_UNSET;
	for (i = 0; i < Plugins->endlist; i++)
	{
		iplug = &Plugins->plist[i];

		if (iplug->status != PL_RUNNING)
			continue;

		api_table = iplug->get_api_post_table(api);
		if (!api_table) {
			//plugin doesn't provide this api table
			continue;
		}

		pfn_routine = get_api_function(api_table, func_offset);
		if (!pfn_routine) {
			//plugin doesn't provide this function
			continue;
		}

		// initialize PublicMetaGlobals
		PublicMetaGlobals.mres = MRES_UNSET;
		PublicMetaGlobals.prev_mres = prev_mres;
		PublicMetaGlobals.status = status;

		// call plugin
		api_info->api_caller(pfn_routine, packed_args);

		// plugin's result code
		mres = PublicMetaGlobals.mres;
		if (mres > status)
			status = mres;

		// save this for successive plugins to see
		prev_mres = mres;
	}

	if (--call_count > 0)
	{
		//Restore backup
		PublicMetaGlobals = backup_meta_globals[0];
	}
}

// full return typed version of main hook function
void *main_hook_function(const class_ret_t ret_init, unsigned int api_info_offset, enum_api_t api, unsigned int func_offset, const void *packed_args) noexcept
{
	const api_info_t *api_info;
	int i;
	META_RES mres, status, prev_mres;
	MPlugin *iplug;
	void *pfn_routine;
	int loglevel;
	const void *api_table;
	meta_globals_t backup_meta_globals[1];

	//passing offset from api wrapper function makes code faster/smaller
	api_info = get_api_info(api, api_info_offset);

	//Fix bug with metamod-bot-plugins.
	if (call_count++ > 0) {
		//Backup PublicMetaGlobals.
		backup_meta_globals[0] = PublicMetaGlobals;
	}

	//Return class setup
	class_ret_t dllret = ret_init;
	class_ret_t override_ret = ret_init;
	class_ret_t pub_override_ret = ret_init;
	class_ret_t orig_ret = ret_init;
	class_ret_t pub_orig_ret = ret_init;

	//Setup
	loglevel = api_info->loglevel;
	mres = MRES_UNSET;
	status = MRES_UNSET;
	prev_mres = MRES_UNSET;
	pfn_routine = nullptr;

	//Pre plugin functions
	prev_mres = MRES_UNSET;
	for (i = 0; i < Plugins->endlist; i++)
	{
		iplug = &Plugins->plist[i];

		if (iplug->status != PL_RUNNING)
			continue;

		api_table = iplug->get_api_table(api);
		if (!api_table) {
			//plugin doesn't provide this api table
			continue;
		}

		pfn_routine = get_api_function(api_table, func_offset);
		if (!pfn_routine) {
			//plugin doesn't provide this function
			continue;
		}

		// initialize PublicMetaGlobals
		PublicMetaGlobals.mres = MRES_UNSET;
		PublicMetaGlobals.prev_mres = prev_mres;
		PublicMetaGlobals.status = status;
		pub_orig_ret = orig_ret;
		PublicMetaGlobals.orig_ret = pub_orig_ret.getptr();
		if (status == MRES_SUPERCEDE) {
			pub_override_ret = override_ret;
			PublicMetaGlobals.override_ret = pub_override_ret.getptr();
		}

		// call plugin
		dllret = class_ret_t(api_info->api_caller(pfn_routine, packed_args));

		// plugin's result code
		mres = PublicMetaGlobals.mres;
		if (mres > status)
			status = mres;

		// save this for successive plugins to see
		prev_mres = mres;

		if (mres == MRES_SUPERCEDE) {
			pub_override_ret = dllret;
			override_ret = dllret;
		}
	}

	call_count--;

	//Api call
	if (status != MRES_SUPERCEDE) {
		//get api table
		api_table = *api_tables[api];

		if (api_table)
		{
			if (pfn_routine = get_api_function(api_table, func_offset); pfn_routine)
			{
				dllret = class_ret_t(api_info->api_caller(pfn_routine, packed_args));
				orig_ret = dllret;
			}
			else
			{
				// don't complain for NULL routines in NEW_DLL_FUNCTIONS
				status = MRES_UNSET;
			}
		}
		else
		{
			// don't complain for NULL NEW_DLL_FUNCTIONS-table
			status = MRES_UNSET;
		}
	}
	else
	{
		orig_ret = override_ret;
		pub_orig_ret = override_ret;
		PublicMetaGlobals.orig_ret = pub_orig_ret.getptr();
	}

	call_count++;

	//Post plugin functions
	prev_mres = MRES_UNSET;
	for (i = 0; i < Plugins->endlist; i++)
	{
		iplug = &Plugins->plist[i];

		if (iplug->status != PL_RUNNING)
			continue;

		api_table = iplug->get_api_post_table(api);
		if (!api_table) {
			//plugin doesn't provide this api table
			continue;
		}

		pfn_routine = get_api_function(api_table, func_offset);
		if (!pfn_routine) {
			//plugin doesn't provide this function
			continue;
		}

		// initialize PublicMetaGlobals
		PublicMetaGlobals.mres = MRES_UNSET;
		PublicMetaGlobals.prev_mres = prev_mres;
		PublicMetaGlobals.status = status;
		pub_orig_ret = orig_ret;
		PublicMetaGlobals.orig_ret = pub_orig_ret.getptr();
		if (status == MRES_OVERRIDE) {
			pub_override_ret = override_ret;
			PublicMetaGlobals.override_ret = pub_override_ret.getptr();
		}

		// call plugin
		dllret = class_ret_t(api_info->api_caller(pfn_routine, packed_args));

		// plugin's result code
		mres = PublicMetaGlobals.mres;
		if (mres > status)
			status = mres;

		// save this for successive plugins to see
		prev_mres = mres;

		if (mres == MRES_OVERRIDE)
		{
			pub_override_ret = dllret;
			override_ret = dllret;
		}
	}

	if (--call_count > 0) {
		//Restore backup
		PublicMetaGlobals = backup_meta_globals[0];
	}

	//return value is passed through ret_init!
	if (status != MRES_OVERRIDE)
	{
		return(*(void **)orig_ret.getptr());
	}
	else
	{
		return(*(void **)override_ret.getptr());
	}
}
