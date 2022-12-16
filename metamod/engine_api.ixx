export module engine_api;

export import eiface;

// Plugin's GetEngineFunctions, called by metamod.
export using GET_ENGINE_FUNCTIONS_FN = int (*) (enginefuncs_t *pengfuncsFromEngine, int *interfaceVersion);

// According to SDK engine/eiface.h:
//! enginefuncs_t
//! ONLY ADD NEW FUNCTIONS TO THE END OF THIS STRUCT. INTERFACE VERSION IS FROZEN AT 138
export inline constexpr auto ENGINE_INTERFACE_VERSION = 138;

// Protect against other projects which use this include file but use the
// normal enginefuncs_t type for their meta_engfuncs.
//#ifdef __METAMOD_BUILD__
//#include "meta_eiface.h"  // meta_enginefuncs_t
//extern meta_enginefuncs_t meta_engfuncs DLLHIDDEN;
//#else
//extern enginefuncs_t meta_engfuncs DLLHIDDEN;
//#endif

// Typedefs for the above functions:

export using FN_PRECACHEMODEL = int (*) (char *s);
export using FN_PRECACHESOUND = int (*) (char *s);
export using FN_SETMODEL = void (*) (edict_t *e, const char *m);
export using FN_MODELINDEX = int (*) (const char *m);
export using FN_MODELFRAMES = int (*) (int modelIndex);
export using FN_SETSIZE = void (*) (edict_t *e, const float *rgflMin, const float *rgflMax);
export using FN_CHANGELEVEL = void (*) (char *s1, char *s2);
export using FN_GETSPAWNPARMS = void (*) (edict_t *ent);
export using FN_SAVESPAWNPARMS = void (*) (edict_t *ent);
export using FN_VECTOYAW = float (*) (const float *rgflVector);
export using FN_VECTOANGLES = void (*) (const float *rgflVectorIn, float *rgflVectorOut);
export using FN_MOVETOORIGIN = void (*) (edict_t *ent, const float *pflGoal, float dist, int iMoveType);
export using FN_CHANGEYAW = void (*) (edict_t *ent);
export using FN_CHANGEPITCH = void (*) (edict_t *ent);
export using FN_FINDENTITYBYSTRING = edict_t * (*) (edict_t *pEdictStartSearchAfter, const char *pszField, const char *pszValue);
export using FN_GETENTITYILLUM = int (*) (edict_t *pEnt);
export using FN_FINDENTITYINSPHERE = edict_t * (*) (edict_t *pEdictStartSearchAfter, const float *org, float rad);
export using FN_FINDCLIENTINPVS = edict_t * (*) (edict_t *pEdict);
export using FN_ENTITIESINPVS = edict_t * (*) (edict_t *pplayer);
export using FN_MAKEVECTORS = void (*) (const float *rgflVector);
export using FN_ANGLEVECTORS = void (*) (const float *rgflVector, float *forward, float *right, float *up);
export using FN_CREATEENTITY = edict_t * (*) (void);
export using FN_REMOVEENTITY = void (*) (edict_t *e);
export using FN_CREATENAMEDENTITY = edict_t * (*) (int className);
export using FN_MAKESTATIC = void (*) (edict_t *ent);
export using FN_ENTISONFLOOR = int (*) (edict_t *e);
export using FN_DROPTOFLOOR = int (*) (edict_t *e);
export using FN_WALKMOVE = int (*) (edict_t *ent, float yaw, float dist, int iMode);
export using FN_SETORIGIN = void (*) (edict_t *e, const float *rgflOrigin);
export using FN_EMITSOUND = void (*) (edict_t *entity, int channel, const char *sample, /*int*/float volume, float attenuation, int fFlags, int pitch);
export using FN_EMITAMBIENTSOUND = void (*) (edict_t *entity, float *pos, const char *samp, float vol, float attenuation, int fFlags, int pitch);
export using FN_TRACELINE = void (*) (const float *v1, const float *v2, int fNoMonsters, edict_t *pentToSkip, TraceResult *ptr);
export using FN_TRACETOSS = void (*) (edict_t *pent, edict_t *pentToIgnore, TraceResult *ptr);
export using FN_TRACEMONSTERHULL = int (*) (edict_t *pEdict, const float *v1, const float *v2, int fNoMonsters, edict_t *pentToSkip, TraceResult *ptr);
export using FN_TRACEHULL = void (*) (const float *v1, const float *v2, int fNoMonsters, int hullNumber, edict_t *pentToSkip, TraceResult *ptr);
export using FN_TRACEMODEL = void (*) (const float *v1, const float *v2, int hullNumber, edict_t *pent, TraceResult *ptr);
export using FN_TRACETEXTURE = const char * (*) (edict_t *pTextureEntity, const float *v1, const float *v2);
export using FN_TRACESPHERE = void (*) (const float *v1, const float *v2, int fNoMonsters, float radius, edict_t *pentToSkip, TraceResult *ptr);
export using FN_GETAIMVECTOR = void (*) (edict_t *ent, float speed, float *rgflReturn);
export using FN_SERVERCOMMAND = void (*) (char *str);
export using FN_SERVEREXECUTE = void (*) (void);
export using FN_CLIENTCOMMAND_ENG = void (*) (edict_t *pEdict, char *szFmt, ...);
export using FN_PARTICLEEFFECT = void (*) (const float *org, const float *dir, float color, float count);
export using FN_LIGHTSTYLE = void (*) (int style, char *val);
export using FN_DECALINDEX = int (*) (const char *name);
export using FN_POINTCONTENTS = int (*) (const float *rgflVector);
export using FN_MESSAGEBEGIN = void (*) (int msg_dest, int msg_type, const float *pOrigin, edict_t *ed);
export using FN_MESSAGEEND = void (*) (void);
export using FN_WRITEBYTE = void (*) (int iValue);
export using FN_WRITECHAR = void (*) (int iValue);
export using FN_WRITESHORT = void (*) (int iValue);
export using FN_WRITELONG = void (*) (int iValue);
export using FN_WRITEANGLE = void (*) (float flValue);
export using FN_WRITECOORD = void (*) (float flValue);
export using FN_WRITESTRING = void (*) (const char *sz);
export using FN_WRITEENTITY = void (*) (int iValue);
export using FN_CVARREGISTER = void (*) (cvar_t *pCvar);
export using FN_CVARGETFLOAT = float (*) (const char *szVarName);
export using FN_CVARGETSTRING = const char * (*) (const char *szVarName);
export using FN_CVARSETFLOAT = void (*) (const char *szVarName, float flValue);
export using FN_CVARSETSTRING = void (*) (const char *szVarName, const char *szValue);
export using FN_ALERTMESSAGE = void (*) (ALERT_TYPE atype, char *szFmt, ...);
#ifdef HLSDK_3_2_OLD_EIFACE
export using FN_ENGINEFPRINTF = void (*) (FILE *pfile, char *szFmt, ...);
export using FN_PVALLOCENTPRIVATEDATA = void * (*) (edict_t *pEdict, long cb);
#else
export using FN_ENGINEFPRINTF = void (*) (void *pfile, char *szFmt, ...);
export using FN_PVALLOCENTPRIVATEDATA = void * (*) (edict_t *pEdict, std::int32_t cb);
#endif
export using FN_PVENTPRIVATEDATA = void * (*) (edict_t *pEdict);
export using FN_FREEENTPRIVATEDATA = void (*) (edict_t *pEdict);
export using FN_SZFROMINDEX = const char * (*) (int iString);
export using FN_ALLOCSTRING = int (*) (const char *szValue);
export using FN_GETVARSOFENT = entvars_t * (*) (edict_t *pEdict);
export using FN_PENTITYOFENTOFFSET = edict_t * (*) (int iEntOffset);
export using FN_ENTOFFSETOFPENTITY = int (*) (const edict_t *pEdict);
export using FN_INDEXOFEDICT = int (*) (const edict_t *pEdict);
export using FN_PENTITYOFENTINDEX = edict_t * (*) (int iEntIndex);
export using FN_FINDENTITYBYVARS = edict_t * (*) (entvars_t *pvars);
export using FN_GETMODELPTR = void * (*) (edict_t *pEdict);
export using FN_REGUSERMSG = int (*) (const char *pszName, int iSize);
export using FN_ANIMATIONAUTOMOVE = void (*) (const edict_t *pEdict, float flTime);
export using FN_GETBONEPOSITION = void (*) (const edict_t *pEdict, int iBone, float *rgflOrigin, float *rgflAngles);
#ifdef HLSDK_3_2_OLD_EIFACE
export using FN_FUNCTIONFROMNAME = unsigned long (*) (const char *pName);
export using FN_NAMEFORFUNCTION = const char * (*) (unsigned long function);
#else
export using FN_FUNCTIONFROMNAME = std::uint32_t (*) (const char *pName);
export using FN_NAMEFORFUNCTION = const char * (*) (std::uint32_t function);
#endif
export using FN_CLIENTPRINTF = void (*) (edict_t *pEdict, PRINT_TYPE ptype, const char *szMsg);
export using FN_SERVERPRINT = void (*) (const char *szMsg);
export using FN_CMD_ARGS = const char * (*) (void);
export using FN_CMD_ARGV = const char * (*) (int argc);
export using FN_CMD_ARGC = int (*) (void);
export using FN_GETATTACHMENT = void (*) (const edict_t *pEdict, int iAttachment, float *rgflOrigin, float *rgflAngles);
export using FN_CRC32_INIT = void (*) (CRC32_t *pulCRC);
export using FN_CRC32_PROCESSBUFFER = void (*) (CRC32_t *pulCRC, void *p, int len);
export using FN_CRC32_PROCESSBYTE = void (*) (CRC32_t *pulCRC, unsigned char ch);
export using FN_CRC32_FINAL = CRC32_t (*) (CRC32_t pulCRC);
#ifdef HLSDK_3_2_OLD_EIFACE
export using FN_RANDOMLONG = long (*) (long lLow, long lHigh);
#else
export using FN_RANDOMLONG = std::int32_t (*) (std::int32_t lLow, std::int32_t lHigh);
#endif
export using FN_RANDOMFLOAT = float (*) (float flLow, float flHigh);
export using FN_SETVIEW = void (*) (const edict_t *pClient, const edict_t *pViewent);
export using FN_TIME = float (*) (void);
export using FN_CROSSHAIRANGLE = void (*) (const edict_t *pClient, float pitch, float yaw);
export using FN_LOADFILEFORME = byte * (*) (char *filename, int *pLength);
export using FN_FREEFILE = void (*) (void *buffer);
export using FN_ENDSECTION = void (*) (const char *pszSectionName);
export using FN_COMPAREFILETIME = int (*) (char *filename1, char *filename2, int *iCompare);
export using FN_GETGAMEDIR = void (*) (char *szGetGameDir);
export using FN_CVAR_REGISTERVARIABLE = void (*) (cvar_t *variable);
export using FN_FADECLIENTVOLUME = void (*) (const edict_t *pEdict, int fadePercent, int fadeOutSeconds, int holdTime, int fadeInSeconds);
export using FN_SETCLIENTMAXSPEED = void (*) (const edict_t *pEdict, float fNewMaxspeed);
export using FN_CREATEFAKECLIENT = edict_t * (*) (const char *netname);
export using FN_RUNPLAYERMOVE = void (*) (edict_t *fakeclient, const float *viewangles, float forwardmove, float sidemove, float upmove, unsigned short buttons, byte impulse, byte msec);
export using FN_NUMBEROFENTITIES = int (*) (void);
export using FN_GETINFOKEYBUFFER = char * (*) (edict_t *e);
export using FN_INFOKEYVALUE = char * (*) (char *infobuffer, char *key);
export using FN_SETKEYVALUE = void (*) (char *infobuffer, char *key, char *value);
export using FN_SETCLIENTKEYVALUE = void (*) (int clientIndex, char *infobuffer, char *key, char *value);
export using FN_ISMAPVALID = int (*) (char *filename);
export using FN_STATICDECAL = void (*) (const float *origin, int decalIndex, int entityIndex, int modelIndex);
export using FN_PRECACHEGENERIC = int (*) (char *s);
export using FN_GETPLAYERUSERID = int (*) (edict_t *e);
export using FN_BUILDSOUNDMSG = void (*) (edict_t *entity, int channel, const char *sample, /*int*/float volume, float attenuation, int fFlags, int pitch, int msg_dest, int msg_type, const float *pOrigin, edict_t *ed);
export using FN_ISDEDICATEDSERVER = int (*) (void);
export using FN_CVARGETPOINTER = cvar_t * (*) (const char *szVarName);
export using FN_GETPLAYERWONID = unsigned int (*) (edict_t *e);
export using FN_INFO_REMOVEKEY = void (*) (char *s, const char *key);
export using FN_GETPHYSICSKEYVALUE = const char * (*) (const edict_t *pClient, const char *key);
export using FN_SETPHYSICSKEYVALUE = void (*) (const edict_t *pClient, const char *key, const char *value);
export using FN_GETPHYSICSINFOSTRING = const char * (*) (const edict_t *pClient);
export using FN_PRECACHEEVENT = unsigned short (*) (int type, const char *psz);
export using FN_PLAYBACKEVENT = void (*) (int flags, const edict_t *pInvoker, unsigned short eventindex, float delay, float *origin, float *angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2);
export using FN_SETFATPVS = unsigned char * (*) (float *org);
export using FN_SETFATPAS = unsigned char * (*) (float *org);
export using FN_CHECKVISIBILITY = int (*) (const edict_t *entity, unsigned char *pset);
export using FN_DELTASETFIELD = void (*) (struct delta_s *pFields, const char *fieldname);
export using FN_DELTAUNSETFIELD = void (*) (struct delta_s *pFields, const char *fieldname);
export using FN_DELTAADDENCODER = void (*) (char *name, void (*conditionalencode)(struct delta_s *pFields, const unsigned char *from, const unsigned char *to));
export using FN_GETCURRENTPLAYER = int (*) (void);
export using FN_CANSKIPPLAYER = int (*) (const edict_t *player);
export using FN_DELTAFINDFIELD = int (*) (struct delta_s *pFields, const char *fieldname);
export using FN_DELTASETFIELDBYINDEX = void (*) (struct delta_s *pFields, int fieldNumber);
export using FN_DELTAUNSETFIELDBYINDEX = void (*) (struct delta_s *pFields, int fieldNumber);
export using FN_SETGROUPMASK = void (*) (int mask, int op);
export using FN_CREATEINSTANCEDBASELINE = int (*) (int classname, entity_state_t *baseline);
export using FN_CVAR_DIRECTSET = void (*) (cvar_t *var, char *value);
export using FN_FORCEUNMODIFIED = void (*) (FORCE_TYPE type, float *mins, float *maxs, const char *filename);
export using FN_GETPLAYERSTATS = void (*) (const edict_t *pClient, int *ping, int *packet_loss);
export using FN_ADDSERVERCOMMAND = void (*) (char *cmd_name, void (*function) (void));
// Added in SDK 2.2:
export using FN_VOICE_GETCLIENTLISTENING = qboolean (*) (int iReceiver, int iSender);
export using FN_VOICE_SETCLIENTLISTENING = qboolean (*) (int iReceiver, int iSender, qboolean bListen);
// Added for HL 1109 (no SDK update):
export using FN_GETPLAYERAUTHID = const char * (*) (edict_t *e);
// Added 2003/11/10 (no SDK update):
export using FN_SEQUENCEGET = sequenceEntry_s * (*) (const char *fileName, const char *entryName);
export using FN_SEQUENCEPICKSENTENCE = sentenceEntry_s * (*) (const char *groupName, int pickMethod, int *picked);
export using FN_GETFILESIZE = int (*) (char *filename);
export using FN_GETAPPROXWAVEPLAYLEN = unsigned int (*) (const char *filepath);
export using FN_ISCAREERMATCH = int (*) (void);
export using FN_GETLOCALIZEDSTRINGLENGTH = int (*) (const char *label);
export using FN_REGISTERTUTORMESSAGESHOWN = void (*) (int mid);
export using FN_GETTIMESTUTORMESSAGESHOWN = int (*) (int mid);
export using FN_PROCESSTUTORMESSAGEDECAYBUFFER = void (*) (int *buffer, int bufferLength);
export using FN_CONSTRUCTTUTORMESSAGEDECAYBUFFER = void (*) (int *buffer, int bufferLength);
export using FN_RESETTUTORMESSAGEDECAYDATA = void (*) (void);
// Added 2005/08/11 (no SDK update):
export using FN_QUERYCLIENTCVARVALUE = void (*) (const edict_t *player, const char *cvarName);
// Added 2005/11/21 (no SDK update):
export using FN_QUERYCLIENTCVARVALUE2 = void (*) (const edict_t *player, const char *cvarName, int requestID);
// Added 2009/06/17 (no SDK update):
export using FN_ENGCHECKPARM = void (*) (const char *pchCmdLineToken, char **pchNextVal);
