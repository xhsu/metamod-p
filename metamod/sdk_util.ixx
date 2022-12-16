export module sdk_util;

import <cstring>;

export import util;


// Also, create some additional macros for engine callback functions, which
// weren't in SDK dlls/enginecallbacks.h but probably should have been.

#define GET_INFOKEYBUFFER	(*g_engfuncs.pfnGetInfoKeyBuffer)
#define INFOKEY_VALUE		(*g_engfuncs.pfnInfoKeyValue)
#define SET_CLIENT_KEYVALUE	(*g_engfuncs.pfnSetClientKeyValue)
#define REG_SVR_COMMAND		(*g_engfuncs.pfnAddServerCommand)
#define SERVER_PRINT		(*g_engfuncs.pfnServerPrint)
#define SET_SERVER_KEYVALUE	(*g_engfuncs.pfnSetKeyValue)
#define QUERY_CLIENT_CVAR_VALUE		(*g_engfuncs.pfnQueryClientCvarValue)
#define QUERY_CLIENT_CVAR_VALUE2	(*g_engfuncs.pfnQueryClientCvarValue2)

// Add overloaded ENTINDEX() version for const edict_t pointer.
// The pfnIndexOfEdict() function takes a const edict_t pointer
// as parameter anyway, so there is no reason why ENTINDEX()
// shouldn't.
__forceinline int ENTINDEX(const edict_t *pEdict) noexcept
{
	return((*g_engfuncs.pfnIndexOfEdict)(pEdict));
}


// Also, create some nice inlines for engine callback combos.

// Get a setinfo value from a player entity.
export __forceinline char *ENTITY_KEYVALUE(edict_t *entity, char *key) noexcept
{
	return g_engfuncs.pfnInfoKeyValue(g_engfuncs.pfnGetInfoKeyBuffer(entity), key);
}

// Set a setinfo value for a player entity.
export __forceinline void ENTITY_SET_KEYVALUE(edict_t *entity, char *key, char *value) noexcept
{
	SET_CLIENT_KEYVALUE(ENTINDEX(entity), GET_INFOKEYBUFFER(entity), key, value);
}

// Get a "serverinfo" value.
export __forceinline char *SERVERINFO(char *key) noexcept
{
	return ENTITY_KEYVALUE(g_engfuncs.pfnPEntityOfEntIndex(0), key);
}

// Set a "serverinfo" value.
export __forceinline void SET_SERVERINFO(char *key, char *value) noexcept
{
	SET_SERVER_KEYVALUE(GET_INFOKEYBUFFER(g_engfuncs.pfnPEntityOfEntIndex(0)), key, value);
}

// Get a "localinfo" value.
export __forceinline char *LOCALINFO(char *key) noexcept
{
	return(ENTITY_KEYVALUE(nullptr, key));
}

// Set a "localinfo" value.
export __forceinline void SET_LOCALINFO(char *key, char *value) noexcept
{
	SET_SERVER_KEYVALUE(GET_INFOKEYBUFFER(nullptr), key, value);
}

export __forceinline int fast_FNullEnt(const edict_t *pent) noexcept
{
	return(!pent || !(*g_engfuncs.pfnEntOffsetOfPEntity)(pent));
}

// Our slightly modified version, using an edict_t pointer instead of a
// CBaseEntity pointer. (was in 1.17p1, included in 1.17.1)
void META_UTIL_HudMessage(edict_t *pEntity, const hudtextparms_t &textparms, const char *pMessage);

const char *META_UTIL_VarArgs(const char *format, ...);

short FixedSigned16(float value, float scale);
unsigned short FixedUnsigned16(float value, float scale);
