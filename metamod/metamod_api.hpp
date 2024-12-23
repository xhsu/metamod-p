/*

Simplified Version of MetaMod API Header

	Created Date: Sep 26 2024
	Compiler: Luna the Reborn

*/

#if !defined(INCLUDED_IN_MODULE) || defined(__INTELLISENSE__)
#pragma once

#include "../hlsdk/engine/hlsdk.engine.hpp"
#include "../hlsdk/dlls/hlsdk.sv.util.hpp"

#else

import std.compat;

import hlsdk;

#endif

#ifndef EXPORT
#define EXPORT
#endif

#pragma region dllapi.h

// Typedefs for these are provided in SDK engine/eiface.h, but I didn't
// like the names (APIFUNCTION, APIFUNCTION2, NEW_DLL_FUNCTIONS_FN).
export using GETENTITYAPI_FN = int (*) (DLL_FUNCTIONS* pFunctionTable, int interfaceVersion);
export using GETENTITYAPI2_FN = int (*) (DLL_FUNCTIONS* pFunctionTable, int* interfaceVersion);
export using GETNEWDLLFUNCTIONS_FN = int (*) (NEW_DLL_FUNCTIONS* pFunctionTable, int* interfaceVersion);

#pragma endregion

#pragma region engine_api.h

// Plugin's GetEngineFunctions, called by metamod.
export using GET_ENGINE_FUNCTIONS_FN = int (*) (enginefuncs_t* pengfuncsFromEngine, int* interfaceVersion);

// According to SDK engine/eiface.h:
//! enginefuncs_t
//! ONLY ADD NEW FUNCTIONS TO THE END OF THIS STRUCT. INTERFACE VERSION IS FROZEN AT 138
export inline constexpr auto ENGINE_INTERFACE_VERSION = 138;

#pragma endregion

#pragma region plinfo.h

// Flags for plugin to indicate when it can be be loaded/unloaded.
// NOTE: order is crucial, as greater/less comparisons are made.
export enum PLUG_LOADTIME
{
	PT_NEVER = 0,
	PT_STARTUP,			// should only be loaded/unloaded at initial hlds execution
	PT_CHANGELEVEL,		// can be loaded/unloaded between maps
	PT_ANYTIME,			// can be loaded/unloaded at any time
	PT_ANYPAUSE,		// can be loaded/unloaded at any time, and can be "paused" during a map
};

// Flags to indicate why the plugin is being unloaded.
export enum PL_UNLOAD_REASON
{
	PNL_NULL = 0,
	PNL_INI_DELETED,		// was deleted from plugins.ini
	PNL_FILE_NEWER,			// file on disk is newer than last load
	PNL_COMMAND,			// requested by server/console command
	PNL_CMD_FORCED,			// forced by server/console command
	PNL_DELAYED,			// delayed from previous request; can't tell origin
	//only used for 'real_reason' on MPlugin::unload()
	PNL_PLUGIN,				// requested by plugin function call
	PNL_PLG_FORCED,			// forced by plugin function call
	//only used internally for 'meta reload'
	PNL_RELOAD,				// forced unload by reload()
};

// Information plugin provides about itself.
export struct plugin_info_t
{
	const char* ifvers;			// meta_interface version
	const char* name;			// full name of plugin
	const char* version;		// version
	const char* date;			// date
	const char* author;			// author name/email
	const char* url;			// URL
	const char* logtag;			// log message prefix (unused right now)
	PLUG_LOADTIME loadable;		// when loadable
	PLUG_LOADTIME unloadable;	// when unloadable
};

// Plugin identifier, passed to all Meta Utility Functions.
export using plid_t = const plugin_info_t*;

#pragma endregion

#pragma region mutil.h

// max buffer size for printed messages
export inline constexpr auto MAX_LOGMSG_LEN = 1024;

// For GetGameInfo:
export enum ginfo_t
{
	GINFO_NAME = 0,
	GINFO_DESC,
	GINFO_GAMEDIR,
	GINFO_DLL_FULLPATH,
	GINFO_DLL_FILENAME,
	GINFO_REALDLL_FULLPATH,
};

// Meta Utility Function table type.
export struct mutil_funcs_t
{
	void		(*pfnLogConsole)		(plid_t plid, const char* fmt, ...);
	void		(*pfnLogMessage)		(plid_t plid, const char* fmt, ...);
	void		(*pfnLogError)			(plid_t plid, const char* fmt, ...);
	void		(*pfnLogDeveloper)		(plid_t plid, const char* fmt, ...);
	void		(*pfnCenterSay)			(plid_t plid, const char* fmt, ...);
	void		(*pfnCenterSayParms)	(plid_t plid, hudtextparms_t tparms, const char* fmt, ...);
	void		(*pfnCenterSayVarargs)	(plid_t plid, hudtextparms_t tparms, const char* fmt, va_list ap);
	qboolean	(*pfnCallGameEntity)	(plid_t plid, const char* entStr, entvars_t* pev);
	ESvcCommands(*pfnGetUserMsgID)		(plid_t plid, const char* msgname, int* size);
	const char* (*pfnGetUserMsgName)	(plid_t plid, int msgid, int* size);
	const char* (*pfnGetPluginPath)		(plid_t plid);
	const char* (*pfnGetGameInfo)		(plid_t plid, ginfo_t tag);

	int			(*pfnLoadPlugin)		(plid_t plid, const char* cmdline, PLUG_LOADTIME now, void** plugin_handle);
	int			(*pfnUnloadPlugin)		(plid_t plid, const char* cmdline, PLUG_LOADTIME now, PL_UNLOAD_REASON reason);
	int			(*pfnUnloadPluginByHandle)(plid_t plid, void* plugin_handle, PLUG_LOADTIME now, PL_UNLOAD_REASON reason);

	const char* (*pfnIsQueryingClientCvar)(plid_t plid, const edict_t* player);

	int			(*pfnMakeRequestID)		(plid_t plid);

	void		(*pfnGetHookTables)		(plid_t plid, enginefuncs_t** peng, DLL_FUNCTIONS** pdll, NEW_DLL_FUNCTIONS** pnewdll);
};

#pragma endregion

#pragma region meta_api.h
// Version consists of "major:minor", two separate integer numbers.
// Version 1	original
// Version 2	added plugin_info_t **pinfo
// Version 3	init split into query and attach, added detach
// Version 4	added (PLUG_LOADTIME now) to attach
// Version 5	changed mm ifvers int* to string, moved pl ifvers to info
// Version 5:1	added link support for entity "adminmod_timer" (adminmod)
// Version 5:2	added gamedll_funcs to meta_attach() [v1.0-rc2]
// Version 5:3	added mutil_funcs to meta_query() [v1.05]
// Version 5:4	added centersay utility functions [v1.06]
// Version 5:5	added Meta_Init to plugin API [v1.08]
// Version 5:6	added CallGameEntity utility function [v1.09]
// Version 5:7	added GetUserMsgID, GetUserMsgName util funcs [v1.11]
// Version 5:8	added GetPluginPath [v1.11]
// Version 5:9	added GetGameInfo [v1.14]
// Version 5:10 added GINFO_REALDLL_FULLPATH for GetGameInfo [v1.17]
// Version 5:11 added plugin loading and unloading API [v1.18]
// Version 5:12 added IS_QUERYING_CLIENT_CVAR to mutils [v1.18]
// Version 5:13 added MAKE_REQUESTID and GET_HOOK_TABLES to mutils [v1.19]
EXPORT inline constexpr char const META_INTERFACE_VERSION[] = "5:13";

// Flags returned by a plugin's api function.
// NOTE: order is crucial, as greater/less comparisons are made.
EXPORT enum META_RES
{
	MRES_UNSET = 0,
	MRES_IGNORED,		// plugin didn't take any action
	MRES_HANDLED,		// plugin did something, but real function should still be called
	MRES_OVERRIDE,		// call real function, but use my return value
	MRES_SUPERCEDE,		// skip real function; use my return value
};

// Variables provided to plugins.
EXPORT struct meta_globals_s
{
	META_RES mres;			// writable; plugin's return flag
	META_RES prev_mres;		// readable; return flag of the previous plugin called
	META_RES status;		// readable; "highest" return flag so far
	void* orig_ret;			// readable; return value from "real" function
	void* override_ret;		// readable; return value from overriding/superceding plugin
};

EXPORT using meta_globals_t = meta_globals_s;

EXPORT extern "C++" inline meta_globals_t* gpMetaGlobals = nullptr;

EXPORT inline void SET_META_RESULT(META_RES res) noexcept { gpMetaGlobals->mres = res; }

//#define RETURN_META(result) \
//	do { gpMetaGlobals->mres=result; return; } while(0)
//#define RETURN_META_VALUE(result, value) \
//	do { gpMetaGlobals->mres=result; return(value); } while(0)

EXPORT inline decltype(auto) META_RESULT_STATUS(void) noexcept { return gpMetaGlobals->status; }
EXPORT inline decltype(auto) META_RESULT_PREVIOUS(void) noexcept { return gpMetaGlobals->prev_mres; }
EXPORT template <typename T> inline decltype(auto) META_RESULT_ORIG_RET(void) noexcept { return *reinterpret_cast<T*>(gpMetaGlobals->orig_ret); }
EXPORT template <typename T> inline decltype(auto) META_RESULT_OVERRIDE_RET(void) noexcept { return *reinterpret_cast<T*>(gpMetaGlobals->override_ret); }

// Table of getapi functions, retrieved from each plugin.
EXPORT struct META_FUNCTIONS
{
	GETENTITYAPI_FN         pfnGetEntityAPI{};
	GETENTITYAPI_FN         pfnGetEntityAPI_Post{};
	GETENTITYAPI2_FN        pfnGetEntityAPI2{};
	GETENTITYAPI2_FN        pfnGetEntityAPI2_Post{};
	GETNEWDLLFUNCTIONS_FN   pfnGetNewDLLFunctions{};
	GETNEWDLLFUNCTIONS_FN   pfnGetNewDLLFunctions_Post{};
	GET_ENGINE_FUNCTIONS_FN pfnGetEngineFunctions{};
	GET_ENGINE_FUNCTIONS_FN pfnGetEngineFunctions_Post{};
};

// Pair of function tables provided by game DLL.
EXPORT struct gamedll_funcs_t
{
	DLL_FUNCTIONS* dllapi_table;
	NEW_DLL_FUNCTIONS* newapi_table;
};

// Declared in plugin; referenced in macros.
EXPORT extern "C++" inline gamedll_funcs_t* gpGamedllFuncs = nullptr;
EXPORT extern "C++" inline mutil_funcs_t* gpMetaUtilFuncs = nullptr;

// Tell the dll that we'll be loading it as a metamod plugin, in case it
// needs to do something special prior to the standard query/attach
// procedure.  In particular, this will allow for DLL's that can be used as
// both standalone DLL's and metamod plugins. (optional; not required in
// plugin)
EXPORT using META_INIT_FN = void (*) (void) noexcept;

// Get info about plugin, compare meta_interface versions, provide meta
// utility callback functions.
EXPORT using META_QUERY_FN = int (*) (const char* interfaceVersion,
	plugin_info_t const** plinfo,
	mutil_funcs_t* pMetaUtilFuncs
	) noexcept;

// Attach the plugin to the API; get the table of getapi functions; give 
// meta_globals and gamedll_funcs.
EXPORT using META_ATTACH_FN = int (*) (PLUG_LOADTIME now,
	META_FUNCTIONS* pFunctionTable,
	meta_globals_t* pMGlobals,
	gamedll_funcs_t* pGamedllFuncs
	) noexcept;

// Detach the plugin; tell why and when.
EXPORT using META_DETACH_FN = int (*) (PLUG_LOADTIME now, PL_UNLOAD_REASON reason) noexcept;

// Standard HL SDK interface function prototypes. #STUB_FN
//C_DLLEXPORT int GetEntityAPI_Post(DLL_FUNCTIONS *pFunctionTable, int interfaceVersion);
//C_DLLEXPORT int GetEntityAPI2_Post(DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion);

// Additional SDK-like interface function prototypes. #STUB_FN
//C_DLLEXPORT int GetNewDLLFunctions_Post(NEW_DLL_FUNCTIONS *pNewFunctionTable, int *interfaceVersion);
//C_DLLEXPORT int GetEngineFunctions(enginefuncs_t *pengfuncsFromEngine, int *interfaceVersion);
//C_DLLEXPORT int GetEngineFunctions_Post(enginefuncs_t *pengfuncsFromEngine,int *interfaceVersion);

// Convenience macros for accessing GameDLL functions.  Note: these talk
// _directly_ to the gamedll, and are not multiplexed through Metamod to
// the other plugins.

// DLL API functions:
#define MDLL_FUNC	gpGamedllFuncs->dllapi_table

#define MDLL_GameDLLInit				MDLL_FUNC->pfnGameInit
#define MDLL_Spawn						MDLL_FUNC->pfnSpawn
#define MDLL_Think						MDLL_FUNC->pfnThink
#define MDLL_Use						MDLL_FUNC->pfnUse
#define MDLL_Touch						MDLL_FUNC->pfnTouch
#define MDLL_Blocked					MDLL_FUNC->pfnBlocked
#define MDLL_KeyValue					MDLL_FUNC->pfnKeyValue
#define MDLL_Save						MDLL_FUNC->pfnSave
#define MDLL_Restore					MDLL_FUNC->pfnRestore
#define MDLL_ObjectCollsionBox			MDLL_FUNC->pfnAbsBox
#define MDLL_SaveWriteFields			MDLL_FUNC->pfnSaveWriteFields
#define MDLL_SaveReadFields				MDLL_FUNC->pfnSaveReadFields
#define MDLL_SaveGlobalState			MDLL_FUNC->pfnSaveGlobalState
#define MDLL_RestoreGlobalState			MDLL_FUNC->pfnRestoreGlobalState
#define MDLL_ResetGlobalState			MDLL_FUNC->pfnResetGlobalState
#define MDLL_ClientConnect				MDLL_FUNC->pfnClientConnect
#define MDLL_ClientDisconnect			MDLL_FUNC->pfnClientDisconnect
#define MDLL_ClientKill					MDLL_FUNC->pfnClientKill
#define MDLL_ClientPutInServer			MDLL_FUNC->pfnClientPutInServer
#define MDLL_ClientCommand				MDLL_FUNC->pfnClientCommand
#define MDLL_ClientUserInfoChanged		MDLL_FUNC->pfnClientUserInfoChanged
#define MDLL_ServerActivate				MDLL_FUNC->pfnServerActivate
#define MDLL_ServerDeactivate			MDLL_FUNC->pfnServerDeactivate
#define MDLL_PlayerPreThink				MDLL_FUNC->pfnPlayerPreThink
#define MDLL_PlayerPostThink			MDLL_FUNC->pfnPlayerPostThink
#define MDLL_StartFrame					MDLL_FUNC->pfnStartFrame
#define MDLL_ParmsNewLevel				MDLL_FUNC->pfnParmsNewLevel
#define MDLL_ParmsChangeLevel			MDLL_FUNC->pfnParmsChangeLevel
#define MDLL_GetGameDescription			MDLL_FUNC->pfnGetGameDescription
#define MDLL_PlayerCustomization		MDLL_FUNC->pfnPlayerCustomization
#define MDLL_SpectatorConnect			MDLL_FUNC->pfnSpectatorConnect
#define MDLL_SpectatorDisconnect		MDLL_FUNC->pfnSpectatorDisconnect
#define MDLL_SpectatorThink				MDLL_FUNC->pfnSpectatorThink
#define MDLL_Sys_Error					MDLL_FUNC->pfnSys_Error
#define MDLL_PM_Move					MDLL_FUNC->pfnPM_Move
#define MDLL_PM_Init					MDLL_FUNC->pfnPM_Init
#define MDLL_PM_FindTextureType			MDLL_FUNC->pfnPM_FindTextureType
#define MDLL_SetupVisibility			MDLL_FUNC->pfnSetupVisibility
#define MDLL_UpdateClientData			MDLL_FUNC->pfnUpdateClientData
#define MDLL_AddToFullPack				MDLL_FUNC->pfnAddToFullPack
#define MDLL_CreateBaseline				MDLL_FUNC->pfnCreateBaseline
#define MDLL_RegisterEncoders			MDLL_FUNC->pfnRegisterEncoders
#define MDLL_GetWeaponData				MDLL_FUNC->pfnGetWeaponData
#define MDLL_CmdStart					MDLL_FUNC->pfnCmdStart
#define MDLL_CmdEnd						MDLL_FUNC->pfnCmdEnd
#define MDLL_ConnectionlessPacket		MDLL_FUNC->pfnConnectionlessPacket
#define MDLL_GetHullBounds				MDLL_FUNC->pfnGetHullBounds
#define MDLL_CreateInstancedBaselines	MDLL_FUNC->pfnCreateInstancedBaselines
#define MDLL_InconsistentFile			MDLL_FUNC->pfnInconsistentFile
#define MDLL_AllowLagCompensation		MDLL_FUNC->pfnAllowLagCompensation

// NEW API functions:
#define MNEW_FUNC	gpGamedllFuncs->newapi_table

#define MNEW_OnFreeEntPrivateData		MNEW_FUNC->pfnOnFreeEntPrivateData
#define MNEW_GameShutdown				MNEW_FUNC->pfnGameShutdown
#define MNEW_ShouldCollide				MNEW_FUNC->pfnShouldCollide
#define MNEW_CvarValue					MNEW_FUNC->pfnCvarValue

#pragma endregion
