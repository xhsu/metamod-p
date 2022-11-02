export module dllapi;

export import eiface;

// Typedefs for these are provided in SDK engine/eiface.h, but I didn't
// like the names (APIFUNCTION, APIFUNCTION2, NEW_DLL_FUNCTIONS_FN).
export using GETENTITYAPI_FN = int (*) (DLL_FUNCTIONS *pFunctionTable, int interfaceVersion);
export using GETENTITYAPI2_FN = int (*) (DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion);
export using GETNEWDLLFUNCTIONS_FN = int (*) (NEW_DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion);

// #FN_STUB
// From SDK dlls/cbase.h:
//C_DLLEXPORT int GetEntityAPI(DLL_FUNCTIONS *pFunctionTable, int interfaceVersion);
//C_DLLEXPORT int GetEntityAPI2(DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion);

// No example in SDK..
// From Adminmod dll.cpp:
//C_DLLEXPORT int GetNewDLLFunctions(NEW_DLL_FUNCTIONS *pNewFunctionTable, int *interfaceVersion);

// Typedefs for the above functions:

export using FN_GAMEINIT = void (*) (void);
export using FN_DISPATCHSPAWN = int (*) (edict_t *pent);
export using FN_DISPATCHTHINK = void (*) (edict_t *pent);
export using FN_DISPATCHUSE = void (*) (edict_t *pentUsed, edict_t *pentOther);
export using FN_DISPATCHTOUCH = void (*) (edict_t *pentTouched, edict_t *pentOther);
export using FN_DISPATCHBLOCKED = void (*) (edict_t *pentBlocked, edict_t *pentOther);
export using FN_DISPATCHKEYVALUE = void (*) (edict_t *pentKeyvalue, KeyValueData *pkvd);
export using FN_DISPATCHSAVE = void (*) (edict_t *pent, SAVERESTOREDATA *pSaveData);
export using FN_DISPATCHRESTORE = int (*) (edict_t *pent, SAVERESTOREDATA *pSaveData, int globalEntity);
export using FN_DISPATCHOBJECTCOLLISIONBOX = void (*) (edict_t *pent);
export using FN_SAVEWRITEFIELDS = void (*) (SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount);
export using FN_SAVEREADFIELDS = void (*) (SAVERESTOREDATA *pSaveData, const char *pname, void *pBaseData, TYPEDESCRIPTION *pFields, int fieldCount);
export using FN_SAVEGLOBALSTATE = void (*) (SAVERESTOREDATA *pSaveData);
export using FN_RESTOREGLOBALSTATE = void (*) (SAVERESTOREDATA *pSaveData);
export using FN_RESETGLOBALSTATE = void (*) (void);

export using FN_CLIENTCONNECT = qboolean(*) (edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]);
export using FN_CLIENTDISCONNECT = void (*) (edict_t *pEntity);
export using FN_CLIENTKILL = void (*) (edict_t *pEntity);
export using FN_CLIENTPUTINSERVER = void (*) (edict_t *pEntity);
export using FN_CLIENTCOMMAND = void (*) (edict_t *pEntity);
export using FN_CLIENTUSERINFOCHANGED = void (*) (edict_t *pEntity, char *infobuffer);
export using FN_SERVERACTIVATE = void (*) (edict_t *pEdictList, int edictCount, int clientMax);
export using FN_SERVERDEACTIVATE = void (*) (void);
export using FN_PLAYERPRETHINK = void (*) (edict_t *pEntity);
export using FN_PLAYERPOSTTHINK = void (*) (edict_t *pEntity);
export using FN_STARTFRAME = void (*) (void);
export using FN_PARMSNEWLEVEL = void (*) (void);
export using FN_PARMSCHANGELEVEL = void (*) (void);
export using FN_GETGAMEDESCRIPTION = const char *(*) (void);
export using FN_PLAYERCUSTOMIZATION = void (*) (edict_t *pEntity, customization_t *pCust);
export using FN_SPECTATORCONNECT = void (*)  (edict_t *pEntity);
export using FN_SPECTATORDISCONNECT = void (*)  (edict_t *pEntity);
export using FN_SPECTATORTHINK = void (*)  (edict_t *pEntity);
export using FN_SYS_ERROR = void (*) (const char *error_string);

export using FN_PM_MOVE = void (*) (playermove_t *ppmove, int server);
export using FN_PM_INIT = void (*) (playermove_t *ppmove);
export using FN_PM_FINDTEXTURETYPE = char (*) (const char *name);

export using FN_SETUPVISIBILITY = void (*) (edict_t *pViewEntity, edict_t *pClient, unsigned char **pvs, unsigned char **pas);
export using FN_UPDATECLIENTDATA = void (*)  (const edict_t *ent, int sendweapons, clientdata_t *cd);
export using FN_ADDTOFULLPACK = int (*) (entity_state_t *state, int e, edict_t *ent, edict_t *host, int hostflags, int player, unsigned char *pSet);
export using FN_CREATEBASELINE = void (*) (int player, int eindex, entity_state_t *baseline, edict_t *entity, int playermodelindex, vec3_t player_mins, vec3_t player_maxs);
export using FN_REGISTERENCODERS = void (*) (void);
export using FN_GETWEAPONDATA = int (*) (edict_t *player, weapon_data_t *info);
export using FN_CMDSTART = void (*) (const edict_t *player, const usercmd_t *cmd, unsigned int random_seed);
export using FN_CMDEND = void (*)  (const edict_t *player);
export using FN_CONNECTIONLESSPACKET = int (*) (const netadr_t *net_from, const char *args, char *response_buffer, int *response_buffer_size);
export using FN_GETHULLBOUNDS = int (*) (int hullnumber, float *mins, float *maxs);
export using FN_CREATEINSTANCEDBASELINES = void (*)  (void);
export using FN_INCONSISTENTFILE = int (*) (const edict_t *player, const char *filename, char *disconnect_message);
export using FN_ALLOWLAGCOMPENSATION = int (*) (void);

export using FN_ONFREEENTPRIVATEDATA = void (*) (edict_t *pEnt);
export using FN_GAMESHUTDOWN = void (*) (void);
export using FN_SHOULDCOLLIDE = int (*) (edict_t *pentTouched, edict_t *pentOther);
// Added 2005/08/11 (no SDK update):
export using FN_CVARVALUE = void (*)(const edict_t *pEnt, const char *value);
// Added 2005/11/21 (no SDK update):
export using FN_CVARVALUE2 = void (*)(const edict_t *pEnt, int requestID, const char *cvarName, const char *value);
