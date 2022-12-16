module;

//#include "api_hook.h"

export module api_info;

export import types_meta;
export import ret_type;

export inline constexpr auto P_PRE = 0;		// plugin function called before gamedll
export inline constexpr auto P_POST = 1;	// plugin function called after gamedll


// API selector
export enum enum_api_t
{
	e_api_engine = 0,
	e_api_dllapi = 1,
	e_api_newapi = 2,
};

// API caller function prototype
export using api_caller_func_t = void *(*)(const void *func, const void *packed_args);


export struct api_info_t
{
	mBOOL trace;			// if true, log info about this function
	int loglevel;			// level at which to log info about this function
	api_caller_func_t api_caller;	// argument format/type for single-main-hook-function optimization
	const char *name;		// string representation of function name
};


// DLL api functions
export struct dllapi_info_t
{
	api_info_t pfnGameInit;
	api_info_t pfnSpawn;
	api_info_t pfnThink;
	api_info_t pfnUse;
	api_info_t pfnTouch;
	api_info_t pfnBlocked;
	api_info_t pfnKeyValue;
	api_info_t pfnSave;
	api_info_t pfnRestore;
	api_info_t pfnSetAbsBox;
	api_info_t pfnSaveWriteFields;
	api_info_t pfnSaveReadFields;
	api_info_t pfnSaveGlobalState;
	api_info_t pfnRestoreGlobalState;
	api_info_t pfnResetGlobalState;
	api_info_t pfnClientConnect;
	api_info_t pfnClientDisconnect;
	api_info_t pfnClientKill;
	api_info_t pfnClientPutInServer;
	api_info_t pfnClientCommand;
	api_info_t pfnClientUserInfoChanged;
	api_info_t pfnServerActivate;
	api_info_t pfnServerDeactivate;
	api_info_t pfnPlayerPreThink;
	api_info_t pfnPlayerPostThink;
	api_info_t pfnStartFrame;
	api_info_t pfnParmsNewLevel;
	api_info_t pfnParmsChangeLevel;
	api_info_t pfnGetGameDescription;
	api_info_t pfnPlayerCustomization;
	api_info_t pfnSpectatorConnect;
	api_info_t pfnSpectatorDisconnect;
	api_info_t pfnSpectatorThink;
	api_info_t pfnSys_Error;
	api_info_t pfnPM_Move;
	api_info_t pfnPM_Init;
	api_info_t pfnPM_FindTextureType;
	api_info_t pfnSetupVisibility;
	api_info_t pfnUpdateClientData;
	api_info_t pfnAddToFullPack;
	api_info_t pfnCreateBaseline;
	api_info_t pfnRegisterEncoders;
	api_info_t pfnGetWeaponData;
	api_info_t pfnCmdStart;
	api_info_t pfnCmdEnd;
	api_info_t pfnConnectionlessPacket;
	api_info_t pfnGetHullBounds;
	api_info_t pfnCreateInstancedBaselines;
	api_info_t pfnInconsistentFile;
	api_info_t pfnAllowLagCompensation;
	api_info_t END;
};


// "New" api functions
export struct newapi_info_t
{
	api_info_t pfnOnFreeEntPrivateData;
	api_info_t pfnGameShutdown;
	api_info_t pfnShouldCollide;
	// Added 2005/08/11 (no SDK update):
	api_info_t pfnCvarValue;
	// Added 2005/11/21 (no SDK update):
	api_info_t pfnCvarValue2;
	api_info_t END;
};


// Engine functions
export struct engine_info_t
{
	api_info_t pfnPrecacheModel;
	api_info_t pfnPrecacheSound;
	api_info_t pfnSetModel;
	api_info_t pfnModelIndex;
	api_info_t pfnModelFrames;
	api_info_t pfnSetSize;
	api_info_t pfnChangeLevel;
	api_info_t pfnGetSpawnParms;
	api_info_t pfnSaveSpawnParms;
	api_info_t pfnVecToYaw;
	api_info_t pfnVecToAngles;
	api_info_t pfnMoveToOrigin;
	api_info_t pfnChangeYaw;
	api_info_t pfnChangePitch;
	api_info_t pfnFindEntityByString;
	api_info_t pfnGetEntityIllum;
	api_info_t pfnFindEntityInSphere;
	api_info_t pfnFindClientInPVS;
	api_info_t pfnEntitiesInPVS;
	api_info_t pfnMakeVectors;
	api_info_t pfnAngleVectors;
	api_info_t pfnCreateEntity;
	api_info_t pfnRemoveEntity;
	api_info_t pfnCreateNamedEntity;
	api_info_t pfnMakeStatic;
	api_info_t pfnEntIsOnFloor;
	api_info_t pfnDropToFloor;
	api_info_t pfnWalkMove;
	api_info_t pfnSetOrigin;
	api_info_t pfnEmitSound;
	api_info_t pfnEmitAmbientSound;
	api_info_t pfnTraceLine;
	api_info_t pfnTraceToss;
	api_info_t pfnTraceMonsterHull;
	api_info_t pfnTraceHull;
	api_info_t pfnTraceModel;
	api_info_t pfnTraceTexture;
	api_info_t pfnTraceSphere;
	api_info_t pfnGetAimVector;
	api_info_t pfnServerCommand;
	api_info_t pfnServerExecute;
	api_info_t pfnClientCommand;
	api_info_t pfnParticleEffect;
	api_info_t pfnLightStyle;
	api_info_t pfnDecalIndex;
	api_info_t pfnPointContents;
	api_info_t pfnMessageBegin;
	api_info_t pfnMessageEnd;
	api_info_t pfnWriteByte;
	api_info_t pfnWriteChar;
	api_info_t pfnWriteShort;
	api_info_t pfnWriteLong;
	api_info_t pfnWriteAngle;
	api_info_t pfnWriteCoord;
	api_info_t pfnWriteString;
	api_info_t pfnWriteEntity;
	api_info_t pfnCVarRegister;
	api_info_t pfnCVarGetFloat;
	api_info_t pfnCVarGetString;
	api_info_t pfnCVarSetFloat;
	api_info_t pfnCVarSetString;
	api_info_t pfnAlertMessage;
	api_info_t pfnEngineFprintf;
	api_info_t pfnPvAllocEntPrivateData;
	api_info_t pfnPvEntPrivateData;
	api_info_t pfnFreeEntPrivateData;
	api_info_t pfnSzFromIndex;
	api_info_t pfnAllocString;
	api_info_t pfnGetVarsOfEnt;
	api_info_t pfnPEntityOfEntOffset;
	api_info_t pfnEntOffsetOfPEntity;
	api_info_t pfnIndexOfEdict;
	api_info_t pfnPEntityOfEntIndex;
	api_info_t pfnFindEntityByVars;
	api_info_t pfnGetModelPtr;
	api_info_t pfnRegUserMsg;
	api_info_t pfnAnimationAutomove;
	api_info_t pfnGetBonePosition;
	api_info_t pfnFunctionFromName;
	api_info_t pfnNameForFunction;
	api_info_t pfnClientPrintf;
	api_info_t pfnServerPrint;
	api_info_t pfnCmd_Args;
	api_info_t pfnCmd_Argv;
	api_info_t pfnCmd_Argc;
	api_info_t pfnGetAttachment;
	api_info_t pfnCRC32_Init;
	api_info_t pfnCRC32_ProcessBuffer;
	api_info_t pfnCRC32_ProcessByte;
	api_info_t pfnCRC32_Final;
	api_info_t pfnRandomLong;
	api_info_t pfnRandomFloat;
	api_info_t pfnSetView;
	api_info_t pfnTime;
	api_info_t pfnCrosshairAngle;
	api_info_t pfnLoadFileForMe;
	api_info_t pfnFreeFile;
	api_info_t pfnEndSection;
	api_info_t pfnCompareFileTime;
	api_info_t pfnGetGameDir;
	api_info_t pfnCvar_RegisterVariable;
	api_info_t pfnFadeClientVolume;
	api_info_t pfnSetClientMaxspeed;
	api_info_t pfnCreateFakeClient;
	api_info_t pfnRunPlayerMove;
	api_info_t pfnNumberOfEntities;
	api_info_t pfnGetInfoKeyBuffer;
	api_info_t pfnInfoKeyValue;
	api_info_t pfnSetKeyValue;
	api_info_t pfnSetClientKeyValue;
	api_info_t pfnIsMapValid;
	api_info_t pfnStaticDecal;
	api_info_t pfnPrecacheGeneric;
	api_info_t pfnGetPlayerUserId;
	api_info_t pfnBuildSoundMsg;
	api_info_t pfnIsDedicatedServer;
	api_info_t pfnCVarGetPointer;
	api_info_t pfnGetPlayerWONId;
	api_info_t pfnInfo_RemoveKey;
	api_info_t pfnGetPhysicsKeyValue;
	api_info_t pfnSetPhysicsKeyValue;
	api_info_t pfnGetPhysicsInfoString;
	api_info_t pfnPrecacheEvent;
	api_info_t pfnPlaybackEvent;
	api_info_t pfnSetFatPVS;
	api_info_t pfnSetFatPAS;
	api_info_t pfnCheckVisibility;
	api_info_t pfnDeltaSetField;
	api_info_t pfnDeltaUnsetField;
	api_info_t pfnDeltaAddEncoder;
	api_info_t pfnGetCurrentPlayer;
	api_info_t pfnCanSkipPlayer;
	api_info_t pfnDeltaFindField;
	api_info_t pfnDeltaSetFieldByIndex;
	api_info_t pfnDeltaUnsetFieldByIndex;
	api_info_t pfnSetGroupMask;
	api_info_t pfnCreateInstancedBaseline;
	api_info_t pfnCvar_DirectSet;
	api_info_t pfnForceUnmodified;
	api_info_t pfnGetPlayerStats;
	api_info_t pfnAddServerCommand;
	// Added in SDK 2.2:
	api_info_t pfnVoice_GetClientListening;
	api_info_t pfnVoice_SetClientListening;
	// Added for HL 1109 (no SDK update):
	api_info_t pfnGetPlayerAuthId;
	// Added 2003/11/10 (no SDK update):
	api_info_t pfnSequenceGet;
	api_info_t pfnSequencePickSentence;
	api_info_t pfnGetFileSize;
	api_info_t pfnGetApproxWavePlayLen;
	api_info_t pfnIsCareerMatch;
	api_info_t pfnGetLocalizedStringLength;
	api_info_t pfnRegisterTutorMessageShown;
	api_info_t pfnGetTimesTutorMessageShown;
	api_info_t pfnProcessTutorMessageDecayBuffer;
	api_info_t pfnConstructTutorMessageDecayBuffer;
	api_info_t pfnResetTutorMessageDecayData;
	// Added 2005/08/11 (no SDK update):
	api_info_t pfnQueryClientCvarValue;
	// Added 2005/11/21 (no SDK update):
	api_info_t pfnQueryClientCvarValue2;
	// Added 2009/06/17 (no SDK update):
	api_info_t pfnEngCheckParm;
	// end
	api_info_t END;
};

// Compine 4 parts for single name
#define _COMBINE4(w,x,y,z) w##x##y##z
#define _COMBINE2(x,y) x##y

// simplified 'void' version of main hook function
void main_hook_function_void(unsigned int api_info_offset, enum_api_t api, unsigned int func_offset, const void *packed_args);

// full return typed version of main hook function
void *main_hook_function(const class_ret_t ret_init, unsigned int api_info_offset, enum_api_t api, unsigned int func_offset, const void *packed_args);

//
// API function args structures/classes
//
#define API_PACK_ARGS(type, args) \
	_COMBINE2(pack_args_type_, type) packed_args args;

#define PACK_ARGS_CLASS_HEADER(type, constructor_args) \
	class _COMBINE2(pack_args_type_, type) : public class_metamod_new { \
		public: inline _COMBINE2(pack_args_type_, type) constructor_args

#define PACK_ARGS_END };

#define VOID_ARG 0

PACK_ARGS_CLASS_HEADER(void, (int)) {};
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(i, (int _i1)) : i1(_i1) {};
int i1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2i, (int _i1, int _i2)) : i1(_i1), i2(_i2) {};
int i1, i2;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(3i, (int _i1, int _i2, int _i3)) : i1(_i1), i2(_i2), i3(_i3) {};
int i1, i2, i3;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(ui, (unsigned int _ui1)) : ui1(_ui1) {};
unsigned int ui1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(ul, (unsigned long _ul1)) : ul1(_ul1) {};
unsigned long ul1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(f, (float _f1)) : f1(_f1) {};
float f1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2f, (float _f1, float _f2)) : f1(_f1), f2(_f2) {};
float f1, f2;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(p, (const void *_p1)) : p1(_p1) {};
const void *p1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2p, (const void *_p1, const void *_p2)) : p1(_p1), p2(_p2) {};
const void *p1, *p2;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(3p, (const void *_p1, const void *_p2, const void *_p3)) : p1(_p1), p2(_p2), p3(_p3) {};
const void *p1, *p2, *p3;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(4p, (const void *_p1, const void *_p2, const void *_p3, const void *_p4)) : p1(_p1), p2(_p2), p3(_p3), p4(_p4) {};
const void *p1, *p2, *p3, *p4;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2pV, (const void *_p1, const void *_p2, const void *_str)) : p1(_p1), p2(_p2), str(_str) {};
const void *p1, *p2, *str;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(ipV, (int _i1, const void *_p1, const void *_str)) : i1(_i1), p1(_p1), str(_str) {};
int i1;
const void *p1, *str;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2i2p, (int _i1, int _i2, const void *_p1, const void *_p2)) : i1(_i1), i2(_i2), p1(_p1), p2(_p2) {};
int i1, i2;
const void *p1, *p2;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2p2f, (const void *_p1, const void *_p2, float _f1, float _f2)) : p1(_p1), p2(_p2), f1(_f1), f2(_f2) {};
const void *p1, *p2;
float f1, f2;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2p2i2p, (const void *_p1, const void *_p2, int _i1, int _i2, const void *_p3, const void *_p4)) : p1(_p1), p2(_p2), i1(_i1), i2(_i2), p3(_p3), p4(_p4) {};
const void *p1, *p2;
int i1, i2;
const void *p3, *p4;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2p3fus2uc, (const void *_p1, const void *_p2, float _f1, float _f2, float _f3, unsigned short _us1, unsigned char _uc1, unsigned char _uc2)) : p1(_p1), p2(_p2), f1(_f1), f2(_f2), f3(_f3), us1(_us1), uc1(_uc1), uc2(_uc2) {};
const void *p1, *p2;
float f1, f2, f3;
unsigned int us1;
unsigned int uc1, uc2;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2pf, (const void *_p1, const void *_p2, float _f1)) : p1(_p1), p2(_p2), f1(_f1) {};
const void *p1, *p2;
float f1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2pfi, (const void *_p1, const void *_p2, float _f1, int _i1)) : p1(_p1), p2(_p2), f1(_f1), i1(_i1) {};
const void *p1, *p2;
float f1;
int i1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2pi, (const void *_p1, const void *_p2, int _i1)) : p1(_p1), p2(_p2), i1(_i1) {};
const void *p1, *p2;
int i1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2pi2p, (const void *_p1, const void *_p2, int _i1, const void *_p3, const void *_p4)) : p1(_p1), p2(_p2), i1(_i1), p3(_p3), p4(_p4) {};
const void *p1, *p2;
int i1;
const void *p3, *p4;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2pif2p, (const void *_p1, const void *_p2, int _i1, float _f1, const void *_p3, const void *_p4)) : p1(_p1), p2(_p2), i1(_i1), f1(_f1), p3(_p3), p4(_p4) {};
const void *p1, *p2;
int i1;
float f1;
const void *p3, *p4;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(3p2f2i, (const void *_p1, const void *_p2, const void *_p3, float _f1, float _f2, int _i1, int _i2)) : p1(_p1), p2(_p2), p3(_p3), f1(_f1), f2(_f2), i1(_i1), i2(_i2) {};
const void *p1, *p2, *p3;
float f1, f2;
int i1, i2;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(3pi2p, (const void *_p1, const void *_p2, const void *_p3, int _i1, const void *_p4, const void *_p5)) : p1(_p1), p2(_p2), p3(_p3), i1(_i1), p4(_p4), p5(_p5) {};
const void *p1, *p2, *p3;
int i1;
const void *p4, *p5;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(i3p, (int _i1, const void *_p1, const void *_p2, const void *_p3)) : i1(_i1), p1(_p1), p2(_p2), p3(_p3) {};
int i1;
const void *p1, *p2, *p3;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(ip, (int _i1, const void *_p1)) : i1(_i1), p1(_p1) {};
int i1;
const void *p1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(ipusf2p2f4i, (int _i1, const void *_p1, unsigned short _us1, float _f1, const void *_p2, const void *_p3, float _f2, float _f3, int _i2, int _i3, int _i4, int _i5)) : i1(_i1), p1(_p1), us1(_us1), f1(_f1), p2(_p2), p3(_p3), f2(_f2), f3(_f3), i2(_i2), i3(_i3), i4(_i4), i5(_i5) {};
int i1;
const void *p1;
unsigned int us1;
float f1;
const void *p2, *p3;
float f2, f3;
int i2, i3, i4, i5;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(3pi, (const void *_p1, const void *_p2, const void *_p3, int _i1)) : p1(_p1), p2(_p2), p3(_p3), i1(_i1) {};
const void *p1, *p2, *p3;
int i1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(4pi, (const void *_p1, const void *_p2, const void *_p3, const void *_p4, int _i1)) : p1(_p1), p2(_p2), p3(_p3), p4(_p4), i1(_i1) {};
const void *p1, *p2, *p3, *p4;
int i1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(pf, (const void *_p1, float _f1)) : p1(_p1), f1(_f1) {};
const void *p1;
float f1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(pfp, (const void *_p1, float _f1, const void *_p2)) : p1(_p1), f1(_f1), p2(_p2) {};
const void *p1;
float f1;
const void *p2;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(pi, (const void *_p1, int _i1)) : p1(_p1), i1(_i1) {};
const void *p1;
int i1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(pi2p, (const void *_p1, int _i1, const void *_p2, const void *_p3)) : p1(_p1), i1(_i1), p2(_p2), p3(_p3) {};
const void *p1;
int i1;
const void *p2, *p3;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(pip, (const void *_p1, int _i1, const void *_p2)) : p1(_p1), i1(_i1), p2(_p2) {};
const void *p1;
int i1;
const void *p2;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(pip2f2i, (const void *_p1, int _i1, const void *_p2, float _f1, float _f2, int _i2, int _i3)) : p1(_p1), i1(_i1), p2(_p2), f1(_f1), f2(_f2), i2(_i2), i3(_i3) {};
const void *p1;
int i1;
const void *p2;
float f1, f2;
int i2, i3;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(pip2f4i2p, (const void *_p1, int _i1, const void *_p2, float _f1, float _f2, int _i2, int _i3, int _i4, int _i5, const void *_p3, const void *_p4)) : p1(_p1), i1(_i1), p2(_p2), f1(_f1), f2(_f2), i2(_i2), i3(_i3), i4(_i4), i5(_i5), p3(_p3), p4(_p4) {};
const void *p1;
int i1;
const void *p2;
float f1, f2;
int i2, i3, i4, i5;
const void *p3, *p4;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(puc, (const void *_p1, unsigned char _uc1)) : p1(_p1), uc1(_uc1) {};
const void *p1;
unsigned int uc1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2i2pi2p, (int _i1, int _i2, const void *_p1, const void *_p2, int _i3, const void *_p3, const void *_p4)) : i1(_i1), i2(_i2), p1(_p1), p2(_p2), i3(_i3), p3(_p3), p4(_p4) {};
int i1, i2;
const void *p1, *p2;
int i3;
const void *p3, *p4;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(2pui, (const void *_p1, const void *_p2, unsigned int _ui1)) : p1(_p1), p2(_p2), ui1(_ui1) {};
const void *p1, *p2;
unsigned int ui1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(i2p, (int _i1, const void *_p1, const void *_p2)) : i1(_i1), p1(_p1), p2(_p2) {};
int i1;
const void *p1, *p2;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(p2f, (const void *_p1, float _f1, float _f2)) : p1(_p1), f1(_f1), f2(_f2) {};
const void *p1;
float f1, f2;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(p2fi, (const void *_p1, float _f1, float _f2, int _i1)) : p1(_p1), f1(_f1), f2(_f2), i1(_i1) {};
const void *p1;
float f1, f2;
int i1;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(p2i, (const void *_p1, int _i1, int _i2)) : p1(_p1), i1(_i1), i2(_i2) {};
const void *p1;
int i1, i2;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(p3i, (const void *_p1, int _i1, int _i2, int _i3)) : p1(_p1), i1(_i1), i2(_i2), i3(_i3) {};
const void *p1;
int i1, i2, i3;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(p4i, (const void *_p1, int _i1, int _i2, int _i3, int _i4)) : p1(_p1), i1(_i1), i2(_i2), i3(_i3), i4(_i4) {};
const void *p1;
int i1, i2, i3, i4;
PACK_ARGS_END

PACK_ARGS_CLASS_HEADER(pi2p2ip, (const void *_p1, int _i1, const void *_p2, const void *_p3, int _i2, int _i3, const void *_p4)) : p1(_p1), i1(_i1), p2(_p2), p3(_p3), i2(_i2), i3(_i3), p4(_p4) {};
const void *p1;
int i1;
const void *p2, *p3;
int i2, i3;
const void *p4;
PACK_ARGS_END

//
// API function callers.
//
#ifdef __METAMOD_BUILD__
#define EXTERN_API_CALLER_FUNCTION(ret_type, args_code) \
		void *_COMBINE4(api_caller_, ret_type, _args_, args_code)(const void * func, const void * packed_args)
#else
#define EXTERN_API_CALLER_FUNCTION(ret_type, args_code) \
		static const api_caller_func_t _COMBINE4(api_caller_, ret_type, _args_, args_code) DLLHIDDEN = (api_caller_func_t)0
#endif

EXTERN_API_CALLER_FUNCTION(void, ipV);
EXTERN_API_CALLER_FUNCTION(void, 2pV);
EXTERN_API_CALLER_FUNCTION(void, void);
EXTERN_API_CALLER_FUNCTION(ptr, void);
EXTERN_API_CALLER_FUNCTION(int, void);
EXTERN_API_CALLER_FUNCTION(float, void);
EXTERN_API_CALLER_FUNCTION(float, 2f);
EXTERN_API_CALLER_FUNCTION(void, 2i);
EXTERN_API_CALLER_FUNCTION(int, 2i);
EXTERN_API_CALLER_FUNCTION(void, 2i2p);
EXTERN_API_CALLER_FUNCTION(void, 2i2pi2p);
EXTERN_API_CALLER_FUNCTION(void, 2p);
EXTERN_API_CALLER_FUNCTION(ptr, 2p);
EXTERN_API_CALLER_FUNCTION(int, 2p);
EXTERN_API_CALLER_FUNCTION(void, 2p2f);
EXTERN_API_CALLER_FUNCTION(void, 2p2i2p);
EXTERN_API_CALLER_FUNCTION(void, 2p3fus2uc);
EXTERN_API_CALLER_FUNCTION(ptr, 2pf);
EXTERN_API_CALLER_FUNCTION(void, 2pfi);
EXTERN_API_CALLER_FUNCTION(void, 2pi);
EXTERN_API_CALLER_FUNCTION(int, 2pi);
EXTERN_API_CALLER_FUNCTION(void, 2pui);
EXTERN_API_CALLER_FUNCTION(void, 2pi2p);
EXTERN_API_CALLER_FUNCTION(void, 2pif2p);
EXTERN_API_CALLER_FUNCTION(int, 3i);
EXTERN_API_CALLER_FUNCTION(void, 3p);
EXTERN_API_CALLER_FUNCTION(ptr, 3p);
EXTERN_API_CALLER_FUNCTION(int, 3p);
EXTERN_API_CALLER_FUNCTION(void, 3p2f2i);
EXTERN_API_CALLER_FUNCTION(int, 3pi2p);
EXTERN_API_CALLER_FUNCTION(void, 4p);
EXTERN_API_CALLER_FUNCTION(int, 4p);
EXTERN_API_CALLER_FUNCTION(void, 4pi);
EXTERN_API_CALLER_FUNCTION(int, 4pi);
EXTERN_API_CALLER_FUNCTION(void, f);
EXTERN_API_CALLER_FUNCTION(void, i);
EXTERN_API_CALLER_FUNCTION(ptr, i);
EXTERN_API_CALLER_FUNCTION(int, i);
EXTERN_API_CALLER_FUNCTION(ptr, ui);
EXTERN_API_CALLER_FUNCTION(uint, ui);
EXTERN_API_CALLER_FUNCTION(ulong, ul);
EXTERN_API_CALLER_FUNCTION(void, i2p);
EXTERN_API_CALLER_FUNCTION(int, i2p);
EXTERN_API_CALLER_FUNCTION(void, i3p);
EXTERN_API_CALLER_FUNCTION(void, ip);
EXTERN_API_CALLER_FUNCTION(ushort, ip);
EXTERN_API_CALLER_FUNCTION(int, ip);
EXTERN_API_CALLER_FUNCTION(void, ipusf2p2f4i);
EXTERN_API_CALLER_FUNCTION(void, p);
EXTERN_API_CALLER_FUNCTION(ptr, p);
EXTERN_API_CALLER_FUNCTION(char, p);
EXTERN_API_CALLER_FUNCTION(int, p);
EXTERN_API_CALLER_FUNCTION(uint, p);
EXTERN_API_CALLER_FUNCTION(float, p);
EXTERN_API_CALLER_FUNCTION(void, p2f);
EXTERN_API_CALLER_FUNCTION(int, p2fi);
EXTERN_API_CALLER_FUNCTION(void, p2i);
EXTERN_API_CALLER_FUNCTION(void, p3i);
EXTERN_API_CALLER_FUNCTION(void, p4i);
EXTERN_API_CALLER_FUNCTION(void, puc);
EXTERN_API_CALLER_FUNCTION(void, pf);
EXTERN_API_CALLER_FUNCTION(void, pfp);
EXTERN_API_CALLER_FUNCTION(void, pi);
EXTERN_API_CALLER_FUNCTION(ptr, pi);
EXTERN_API_CALLER_FUNCTION(int, pi);
EXTERN_API_CALLER_FUNCTION(void, pi2p);
EXTERN_API_CALLER_FUNCTION(int, pi2p2ip);
EXTERN_API_CALLER_FUNCTION(void, pip);
EXTERN_API_CALLER_FUNCTION(ptr, pip);
EXTERN_API_CALLER_FUNCTION(void, pip2f2i);
EXTERN_API_CALLER_FUNCTION(void, pip2f4i2p);

//
// Macros for creating api caller functions
//
#define BEGIN_API_CALLER_FUNC(ret_type, args_type_code) \
	void * _COMBINE4(api_caller_, ret_type, _args_, args_type_code)(const void * func, const void * packed_args) { \
		_COMBINE2(pack_args_type_, args_type_code) * p = (_COMBINE2(pack_args_type_, args_type_code) *)packed_args;

#define END_API_CALLER_FUNC(ret_t, args_t, args) \
		return(*(void **)class_ret_t((*(( ret_t (*) args_t )func)) args).getptr()); \
	}

#define END_API_CALLER_FUNC_void(args_t, args) \
		return((*(( void* (*) args_t )func)) args); \
	}

//
// API function callers.
//

//-
BEGIN_API_CALLER_FUNC(void, ipV)
END_API_CALLER_FUNC_void((int, const void *, ...), (p->i1, p->p1, p->str))

//-
BEGIN_API_CALLER_FUNC(void, 2pV)
END_API_CALLER_FUNC_void((const void *, const void *, ...), (p->p1, p->p2, p->str))

//-
BEGIN_API_CALLER_FUNC(void, void)
END_API_CALLER_FUNC_void((void), ())

BEGIN_API_CALLER_FUNC(ptr, void)
END_API_CALLER_FUNC(void *, (void), ())

BEGIN_API_CALLER_FUNC(int, void)
END_API_CALLER_FUNC(int, (void), ())

BEGIN_API_CALLER_FUNC(float, void)
END_API_CALLER_FUNC(float, (void), ())

//-
BEGIN_API_CALLER_FUNC(float, 2f)
END_API_CALLER_FUNC(float, (float, float), (p->f1, p->f2))

//-
BEGIN_API_CALLER_FUNC(void, 2i)
END_API_CALLER_FUNC_void((int, int), (p->i1, p->i2));

BEGIN_API_CALLER_FUNC(int, 2i)
END_API_CALLER_FUNC(int, (int, int), (p->i1, p->i2));

//-
BEGIN_API_CALLER_FUNC(void, 2i2p)
END_API_CALLER_FUNC_void((int, int, const void *, const void *), (p->i1, p->i2, p->p1, p->p2));

//-
BEGIN_API_CALLER_FUNC(void, 2i2pi2p)
END_API_CALLER_FUNC_void((int, int, const void *, const void *, int, const void *, const void *), (p->i1, p->i2, p->p1, p->p2, p->i3, p->p3, p->p4));

//-
BEGIN_API_CALLER_FUNC(void, 2p)
END_API_CALLER_FUNC_void((const void *, const void *), (p->p1, p->p2));

BEGIN_API_CALLER_FUNC(ptr, 2p)
END_API_CALLER_FUNC(void *, (const void *, const void *), (p->p1, p->p2));

BEGIN_API_CALLER_FUNC(int, 2p)
END_API_CALLER_FUNC(int, (const void *, const void *), (p->p1, p->p2));

//-
BEGIN_API_CALLER_FUNC(void, 2p2f)
END_API_CALLER_FUNC_void((const void *, const void *, float, float), (p->p1, p->p2, p->f1, p->f2));

//-
BEGIN_API_CALLER_FUNC(void, 2p2i2p)
END_API_CALLER_FUNC_void((const void *, const void *, int, int, const void *, const void *), (p->p1, p->p2, p->i1, p->i2, p->p3, p->p4));

//-
BEGIN_API_CALLER_FUNC(void, 2p3fus2uc)
END_API_CALLER_FUNC_void((const void *, const void *, float, float, float, unsigned short, unsigned char, unsigned char), (p->p1, p->p2, p->f1, p->f2, p->f3, p->us1, p->uc1, p->uc2));

//-
BEGIN_API_CALLER_FUNC(ptr, 2pf)
END_API_CALLER_FUNC(void *, (const void *, const void *, float), (p->p1, p->p2, p->f1));

//-
BEGIN_API_CALLER_FUNC(void, 2pfi)
END_API_CALLER_FUNC_void((const void *, const void *, float, int), (p->p1, p->p2, p->f1, p->i1));

//-
BEGIN_API_CALLER_FUNC(void, 2pi)
END_API_CALLER_FUNC_void((const void *, const void *, int), (p->p1, p->p2, p->i1));

BEGIN_API_CALLER_FUNC(int, 2pi)
END_API_CALLER_FUNC(int, (const void *, const void *, int), (p->p1, p->p2, p->i1));

//-
BEGIN_API_CALLER_FUNC(void, 2pui)
END_API_CALLER_FUNC_void((const void *, const void *, unsigned int), (p->p1, p->p2, p->ui1));

//-
BEGIN_API_CALLER_FUNC(void, 2pi2p)
END_API_CALLER_FUNC_void((const void *, const void *, int, const void *, const void *), (p->p1, p->p2, p->i1, p->p3, p->p4));

//-
BEGIN_API_CALLER_FUNC(void, 2pif2p)
END_API_CALLER_FUNC_void((const void *, const void *, int, float, const void *, const void *), (p->p1, p->p2, p->i1, p->f1, p->p3, p->p4));

//-
BEGIN_API_CALLER_FUNC(int, 3i)
END_API_CALLER_FUNC(int, (int, int, int), (p->i1, p->i2, p->i3));

//-
BEGIN_API_CALLER_FUNC(void, 3p)
END_API_CALLER_FUNC_void((const void *, const void *, const void *), (p->p1, p->p2, p->p3));

BEGIN_API_CALLER_FUNC(ptr, 3p)
END_API_CALLER_FUNC(void *, (const void *, const void *, const void *), (p->p1, p->p2, p->p3));

BEGIN_API_CALLER_FUNC(int, 3p)
END_API_CALLER_FUNC(int, (const void *, const void *, const void *), (p->p1, p->p2, p->p3));

//-
BEGIN_API_CALLER_FUNC(void, 3p2f2i)
END_API_CALLER_FUNC_void((const void *, const void *, const void *, float, float, int, int), (p->p1, p->p2, p->p3, p->f1, p->f2, p->i1, p->i2));

//-
BEGIN_API_CALLER_FUNC(int, 3pi2p)
END_API_CALLER_FUNC(int, (const void *, const void *, const void *, int, const void *, const void *), (p->p1, p->p2, p->p3, p->i1, p->p4, p->p5));

//-
BEGIN_API_CALLER_FUNC(void, 4p)
END_API_CALLER_FUNC_void((const void *, const void *, const void *, const void *), (p->p1, p->p2, p->p3, p->p4));

BEGIN_API_CALLER_FUNC(int, 4p)
END_API_CALLER_FUNC(int, (const void *, const void *, const void *, const void *), (p->p1, p->p2, p->p3, p->p4));

//-
BEGIN_API_CALLER_FUNC(void, 4pi)
END_API_CALLER_FUNC_void((const void *, const void *, const void *, const void *, int), (p->p1, p->p2, p->p3, p->p4, p->i1));

BEGIN_API_CALLER_FUNC(int, 4pi)
END_API_CALLER_FUNC(int, (const void *, const void *, const void *, const void *, int), (p->p1, p->p2, p->p3, p->p4, p->i1));

//-
BEGIN_API_CALLER_FUNC(void, f)
END_API_CALLER_FUNC_void((float), (p->f1));

//-
BEGIN_API_CALLER_FUNC(void, i)
END_API_CALLER_FUNC_void((int), (p->i1));

BEGIN_API_CALLER_FUNC(int, i)
END_API_CALLER_FUNC(int, (int), (p->i1));

BEGIN_API_CALLER_FUNC(ptr, i)
END_API_CALLER_FUNC(void *, (int), (p->i1));

BEGIN_API_CALLER_FUNC(uint, ui)
END_API_CALLER_FUNC(unsigned int, (unsigned int), (p->ui1));

BEGIN_API_CALLER_FUNC(ptr, ui)
END_API_CALLER_FUNC(void *, (unsigned int), (p->ui1));

//-
BEGIN_API_CALLER_FUNC(ulong, ul)
END_API_CALLER_FUNC(unsigned long, (unsigned long), (p->ul1));

//-
BEGIN_API_CALLER_FUNC(void, i2p)
END_API_CALLER_FUNC_void((int, const void *, const void *), (p->i1, p->p1, p->p2));

BEGIN_API_CALLER_FUNC(int, i2p)
END_API_CALLER_FUNC(int, (int, const void *, const void *), (p->i1, p->p1, p->p2));

//-
BEGIN_API_CALLER_FUNC(void, i3p)
END_API_CALLER_FUNC_void((int, const void *, const void *, const void *), (p->i1, p->p1, p->p2, p->p3));

//-
BEGIN_API_CALLER_FUNC(void, ip)
END_API_CALLER_FUNC_void((int, const void *), (p->i1, p->p1));

BEGIN_API_CALLER_FUNC(ushort, ip)
END_API_CALLER_FUNC(unsigned short, (int, const void *), (p->i1, p->p1));

BEGIN_API_CALLER_FUNC(int, ip)
END_API_CALLER_FUNC(int, (int, const void *), (p->i1, p->p1));

//-
BEGIN_API_CALLER_FUNC(void, ipusf2p2f4i)
END_API_CALLER_FUNC_void((int, const void *, unsigned short, float, const void *, const void *, float, float, int, int, int, int), (p->i1, p->p1, p->us1, p->f1, p->p2, p->p3, p->f2, p->f3, p->i2, p->i3, p->i4, p->i5));

//-
BEGIN_API_CALLER_FUNC(void, p)
END_API_CALLER_FUNC_void((const void *), (p->p1));

BEGIN_API_CALLER_FUNC(ptr, p)
END_API_CALLER_FUNC(void *, (const void *), (p->p1));

BEGIN_API_CALLER_FUNC(char, p)
END_API_CALLER_FUNC(char, (const void *), (p->p1));

BEGIN_API_CALLER_FUNC(int, p)
END_API_CALLER_FUNC(int, (const void *), (p->p1));

BEGIN_API_CALLER_FUNC(uint, p)
END_API_CALLER_FUNC(unsigned int, (const void *), (p->p1));

BEGIN_API_CALLER_FUNC(float, p)
END_API_CALLER_FUNC(float, (const void *), (p->p1));

//-
BEGIN_API_CALLER_FUNC(void, p2f)
END_API_CALLER_FUNC_void((const void *, float, float), (p->p1, p->f1, p->f2));

//-
BEGIN_API_CALLER_FUNC(int, p2fi)
END_API_CALLER_FUNC(int, (const void *, float, float, int), (p->p1, p->f1, p->f2, p->i1));

//-
BEGIN_API_CALLER_FUNC(void, p2i)
END_API_CALLER_FUNC_void((const void *, int, int), (p->p1, p->i1, p->i2));

//-
BEGIN_API_CALLER_FUNC(void, p3i)
END_API_CALLER_FUNC_void((const void *, int, int, int), (p->p1, p->i1, p->i2, p->i3));

//-
BEGIN_API_CALLER_FUNC(void, p4i)
END_API_CALLER_FUNC_void((const void *, int, int, int, int), (p->p1, p->i1, p->i2, p->i3, p->i4));

//-
BEGIN_API_CALLER_FUNC(void, puc)
END_API_CALLER_FUNC_void((const void *, unsigned char), (p->p1, p->uc1));

//-
BEGIN_API_CALLER_FUNC(void, pf)
END_API_CALLER_FUNC_void((const void *, float), (p->p1, p->f1));

//-
BEGIN_API_CALLER_FUNC(void, pfp)
END_API_CALLER_FUNC_void((const void *, float, const void *), (p->p1, p->f1, p->p2));

//-
BEGIN_API_CALLER_FUNC(void, pi)
END_API_CALLER_FUNC_void((const void *, int), (p->p1, p->i1));

BEGIN_API_CALLER_FUNC(ptr, pi)
END_API_CALLER_FUNC(void *, (const void *, int), (p->p1, p->i1));

BEGIN_API_CALLER_FUNC(int, pi)
END_API_CALLER_FUNC(int, (const void *, int), (p->p1, p->i1));

//-
BEGIN_API_CALLER_FUNC(void, pi2p)
END_API_CALLER_FUNC_void((const void *, int, const void *, const void *), (p->p1, p->i1, p->p2, p->p3));

//-
BEGIN_API_CALLER_FUNC(int, pi2p2ip)
END_API_CALLER_FUNC(int, (const void *, int, const void *, const void *, int, int, const void *), (p->p1, p->i1, p->p2, p->p3, p->i2, p->i3, p->p4));

//-
BEGIN_API_CALLER_FUNC(void, pip)
END_API_CALLER_FUNC_void((const void *, int, const void *), (p->p1, p->i1, p->p2));

BEGIN_API_CALLER_FUNC(ptr, pip)
END_API_CALLER_FUNC(void *, (const void *, int, const void *), (p->p1, p->i1, p->p2));

//-
BEGIN_API_CALLER_FUNC(void, pip2f2i)
END_API_CALLER_FUNC_void((const void *, int, const void *, float, float, int, int), (p->p1, p->i1, p->p2, p->f1, p->f2, p->i2, p->i3));

//-
BEGIN_API_CALLER_FUNC(void, pip2f4i2p)
END_API_CALLER_FUNC_void((const void *, int, const void *, float, float, int, int, int, int, const void *, const void *), (p->p1, p->i1, p->p2, p->f1, p->f2, p->i2, p->i3, p->i4, p->i5, p->p3, p->p4));


// trace flag, loglevel, name
export inline constexpr dllapi_info_t dllapi_info =
{
	{ mFALSE,  3,	api_caller_void_args_void, 	"GameDLLInit" },		// pfnGameInit
	{ mFALSE,  10,	api_caller_int_args_p, 		"DispatchSpawn" },		// pfnSpawn
	{ mFALSE,  16,	api_caller_void_args_p,		"DispatchThink" },		// pfnThink
	{ mFALSE,  9,	api_caller_void_args_2p,	"DispatchUse" },		// pfnUse
	{ mFALSE,  11,	api_caller_void_args_2p,	"DispatchTouch" },		// pfnTouch
	{ mFALSE,  9,	api_caller_void_args_2p,	"DispatchBlocked" },		// pfnBlocked
	{ mFALSE,  10,	api_caller_void_args_2p,	"DispatchKeyValue" },		// pfnKeyValue
	{ mFALSE,  9,	api_caller_void_args_2p,	"DispatchSave" },		// pfnSave
	{ mFALSE,  9,	api_caller_int_args_2pi,	"DispatchRestore" },		// pfnRestore
	{ mFALSE,  20,	api_caller_void_args_p,		"DispatchObjectCollsionBox" },	// pfnSetAbsBox
	{ mFALSE,  9,	api_caller_void_args_4pi,	"SaveWriteFields" },		// pfnSaveWriteFields
	{ mFALSE,  9,	api_caller_void_args_4pi,	"SaveReadFields" },		// pfnSaveReadFields
	{ mFALSE,  9,	api_caller_void_args_p,		"SaveGlobalState" },		// pfnSaveGlobalState
	{ mFALSE,  9,	api_caller_void_args_p,		"RestoreGlobalState" },		// pfnRestoreGlobalState
	{ mFALSE,  9,	api_caller_void_args_void, 	"ResetGlobalState" },	// pfnResetGlobalState
	{ mFALSE,  3,	api_caller_int_args_4p, 	"ClientConnect" },		// pfnClientConnect
	{ mFALSE,  3,	api_caller_void_args_p,		"ClientDisconnect" },	// pfnClientDisconnect
	{ mFALSE,  3,	api_caller_void_args_p,		"ClientKill" },			// pfnClientKill
	{ mFALSE,  3,	api_caller_void_args_p,		"ClientPutInServer" },	// pfnClientPutInServer
	{ mFALSE,  9,	api_caller_void_args_p,		"ClientCommand" },		// pfnClientCommand
	{ mFALSE,  11,	api_caller_void_args_2p,	"ClientUserInfoChanged" },	// pfnClientUserInfoChanged
	{ mFALSE,  3,	api_caller_void_args_p2i,	"ServerActivate" },		// pfnServerActivate
	{ mFALSE,  3,	api_caller_void_args_void,	"ServerDeactivate" },	// pfnServerDeactivate
	{ mFALSE,  14,	api_caller_void_args_p,		"PlayerPreThink" },		// pfnPlayerPreThink
	{ mFALSE,  14,	api_caller_void_args_p,		"PlayerPostThink" },	// pfnPlayerPostThink
	{ mFALSE,  18,	api_caller_void_args_void,	"StartFrame" },			// pfnStartFrame
	{ mFALSE,  9,	api_caller_void_args_void,	"ParmsNewLevel" },		// pfnParmsNewLevel
	{ mFALSE,  9,	api_caller_void_args_void,	"ParmsChangeLevel" },	// pfnParmsChangeLevel
	{ mFALSE,  9,	api_caller_ptr_args_void,	"GetGameDescription" },	// pfnGetGameDescription
	{ mFALSE,  9,	api_caller_void_args_2p,	"PlayerCustomization" },	// pfnPlayerCustomization
	{ mFALSE,  9,	api_caller_void_args_p,		"SpectatorConnect" },	// pfnSpectatorConnect
	{ mFALSE,  9,	api_caller_void_args_p,		"SpectatorDisconnect" },	// pfnSpectatorDisconnect
	{ mFALSE,  9,	api_caller_void_args_p,		"SpectatorThink" },		// pfnSpectatorThink
	{ mFALSE,  3,	api_caller_void_args_p,		"Sys_Error" },			// pfnSys_Error
	{ mFALSE,  13,	api_caller_void_args_pi,	"PM_Move" },			// pfnPM_Move
	{ mFALSE,  9,	api_caller_void_args_p,		"PM_Init" },			// pfnPM_Init
	{ mFALSE,  9,	api_caller_char_args_p,		"PM_FindTextureType" },	// pfnPM_FindTextureType
	{ mFALSE,  12,	api_caller_void_args_4p,	"SetupVisibility" },	// pfnSetupVisibility
	{ mFALSE,  12,	api_caller_void_args_pip,	"UpdateClientData" },	// pfnUpdateClientData
	{ mFALSE,  16,	api_caller_int_args_pi2p2ip,	"AddToFullPack" },		// pfnAddToFullPack
	{ mFALSE,  9,	api_caller_void_args_2i2pi2p,	"CreateBaseline" },		// pfnCreateBaseline
	{ mFALSE,  9,	api_caller_void_args_void,	"RegisterEncoders" },	// pfnRegisterEncoders
	{ mFALSE,  9,	api_caller_int_args_2p,		"GetWeaponData" },		// pfnGetWeaponData
	{ mFALSE,  15,	api_caller_void_args_2pui,	"CmdStart" },			// pfnCmdStart
	{ mFALSE,  15,	api_caller_void_args_p,		"CmdEnd" },				// pfnCmdEnd
	{ mFALSE,  9,	api_caller_int_args_4p,		"ConnectionlessPacket" },	// pfnConnectionlessPacket
	{ mFALSE,  9,	api_caller_int_args_i2p,	"GetHullBounds" },		// pfnGetHullBounds
	{ mFALSE,  9,	api_caller_void_args_void,	"CreateInstancedBaselines" },	// pfnCreateInstancedBaselines
	{ mFALSE,  3,	api_caller_int_args_3p,		"InconsistentFile" },	// pfnInconsistentFile
	{ mFALSE,  20,	api_caller_int_args_void,	"AllowLagCompensation" },	// pfnAllowLagCompensation
	{ mFALSE,  0,	nullptr, nullptr },
};

export inline constexpr newapi_info_t newapi_info =
{
	{ mFALSE,  16,	api_caller_void_args_p,		"OnFreeEntPrivateData" },	// pfnOnFreeEntPrivateData
	{ mFALSE,  3,	api_caller_void_args_void,	"GameShutdown" },			// pfnGameShutdown
	{ mFALSE,  14,	api_caller_int_args_2p,		"ShouldCollide" },			// pfnShouldCollide
	// Added 2005/08/11 (no SDK update):
	{ mFALSE,  3,	api_caller_void_args_2p,	"CvarValue" },			// pfnCvarValue
	// Added 2005/11/21 (no SDK update):
	{ mFALSE,  3,	api_caller_void_args_pi2p,	"CvarValue2" },			// pfnCvarValue2
	{ mFALSE,  0,	nullptr, nullptr },
};

export inline constexpr engine_info_t engine_info =
{
	{ mFALSE,  13,	api_caller_int_args_p,		"PrecacheModel" },		// pfnPrecacheModel
	{ mFALSE,  13,	api_caller_int_args_p,		"PrecacheSound" },		// pfnPrecacheSound
	{ mFALSE,  18,	api_caller_void_args_2p,	"SetModel" },			// pfnSetModel
	{ mFALSE,  34,	api_caller_int_args_p,		"ModelIndex" },			// pfnModelIndex
	{ mFALSE,  10,	api_caller_int_args_i,		"ModelFrames" },		// pfnModelFrames
	{ mFALSE,  14,	api_caller_void_args_3p,	"SetSize" },			// pfnSetSize
	{ mFALSE,  9,	api_caller_void_args_2p,	"ChangeLevel" },		// pfnChangeLevel
	{ mFALSE,  9,	api_caller_void_args_p,		"GetSpawnParms" },		// pfnGetSpawnParms
	{ mFALSE,  9,	api_caller_void_args_p,		"SaveSpawnParms" },		// pfnSaveSpawnParms
	{ mFALSE,  9,	api_caller_float_args_p,	"VecToYaw" },			// pfnVecToYaw
	{ mFALSE,  14,	api_caller_void_args_2p,	"VecToAngles" },		// pfnVecToAngles
	{ mFALSE,  9,	api_caller_void_args_2pfi,	"MoveToOrigin" },		// pfnMoveToOrigin
	{ mFALSE,  9,	api_caller_void_args_p,		"ChangeYaw" },			// pfnChangeYaw
	{ mFALSE,  9,	api_caller_void_args_p,		"ChangePitch" },		// pfnChangePitch
	{ mFALSE,  32,	api_caller_ptr_args_3p,		"FindEntityByString" },		// pfnFindEntityByString
	{ mFALSE,  9,	api_caller_int_args_p,		"GetEntityIllum" },		// pfnGetEntityIllum
	{ mFALSE,  9,	api_caller_ptr_args_2pf,	"FindEntityInSphere" },		// pfnFindEntityInSphere
	{ mFALSE,  19,	api_caller_ptr_args_p,		"FindClientInPVS" },		// pfnFindClientInPVS
	{ mFALSE,  9,	api_caller_ptr_args_p,		"EntitiesInPVS" },		// pfnEntitiesInPVS
	{ mFALSE,  40,	api_caller_void_args_p,		"MakeVectors" },		// pfnMakeVectors
	{ mFALSE,  9,	api_caller_void_args_4p,	"AngleVectors" },		// pfnAngleVectors
	{ mFALSE,  13,	api_caller_ptr_args_void,	"CreateEntity" },		// pfnCreateEntity
	{ mFALSE,  13,	api_caller_void_args_p,		"RemoveEntity" },		// pfnRemoveEntity
	{ mFALSE,  13,	api_caller_ptr_args_i,		"CreateNamedEntity" },		// pfnCreateNamedEntity
	{ mFALSE,  9,	api_caller_void_args_p,		"MakeStatic" },			// pfnMakeStatic
	{ mFALSE,  9,	api_caller_int_args_p,		"EntIsOnFloor" },		// pfnEntIsOnFloor
	{ mFALSE,  9,	api_caller_int_args_p,		"DropToFloor" },		// pfnDropToFloor
	{ mFALSE,  9,	api_caller_int_args_p2fi,	"WalkMove" },			// pfnWalkMove
	{ mFALSE,  14,	api_caller_void_args_2p,	"SetOrigin" },			// pfnSetOrigin
	{ mFALSE,  12,	api_caller_void_args_pip2f2i,	"EmitSound" },			// pfnEmitSound
	{ mFALSE,  12,	api_caller_void_args_3p2f2i,	"EmitAmbientSound" },		// pfnEmitAmbientSound
	{ mFALSE,  20,	api_caller_void_args_2pi2p,	"TraceLine" },			// pfnTraceLine
	{ mFALSE,  9,	api_caller_void_args_3p,	"TraceToss" },			// pfnTraceToss
	{ mFALSE,  9,	api_caller_int_args_3pi2p,	"TraceMonsterHull" },		// pfnTraceMonsterHull
	{ mFALSE,  9,	api_caller_void_args_2p2i2p,	"TraceHull" },			// pfnTraceHull
	{ mFALSE,  9,	api_caller_void_args_2pi2p,	"TraceModel" },			// pfnTraceModel
	{ mFALSE,  15,	api_caller_ptr_args_3p,		"TraceTexture" },		// pfnTraceTexture		// CS: when moving
	{ mFALSE,  9,	api_caller_void_args_2pif2p,	"TraceSphere" },		// pfnTraceSphere
	{ mFALSE,  9,	api_caller_void_args_pfp,	"GetAimVector" },		// pfnGetAimVector
	{ mFALSE,  9,	api_caller_void_args_p,		"ServerCommand" },		// pfnServerCommand
	{ mFALSE,  9,	api_caller_void_args_void,	"ServerExecute" },		// pfnServerExecute
	{ mFALSE,  11,	api_caller_void_args_2pV,	"engClientCommand" },		// pfnClientCommand		// d'oh, ClientCommand in dllapi too
	{ mFALSE,  9,	api_caller_void_args_2p2f,	"ParticleEffect" },		// pfnParticleEffect
	{ mFALSE,  9,	api_caller_void_args_ip,	"LightStyle" },			// pfnLightStyle
	{ mFALSE,  9,	api_caller_int_args_p,		"DecalIndex" },			// pfnDecalIndex
	{ mFALSE,  15,	api_caller_int_args_p,		"PointContents" },		// pfnPointContents		// CS: when moving
	{ mFALSE,  22,	api_caller_void_args_2i2p,	"MessageBegin" },		// pfnMessageBegin
	{ mFALSE,  22,	api_caller_void_args_void,	"MessageEnd" },			// pfnMessageEnd
	{ mFALSE,  30,	api_caller_void_args_i,		"WriteByte" },			// pfnWriteByte
	{ mFALSE,  23,	api_caller_void_args_i,		"WriteChar" },			// pfnWriteChar
	{ mFALSE,  24,	api_caller_void_args_i,		"WriteShort" },			// pfnWriteShort
	{ mFALSE,  23,	api_caller_void_args_i,		"WriteLong" },			// pfnWriteLong
	{ mFALSE,  23,	api_caller_void_args_f,		"WriteAngle" },			// pfnWriteAngle
	{ mFALSE,  23,	api_caller_void_args_f,		"WriteCoord" },			// pfnWriteCoord
	{ mFALSE,  25,	api_caller_void_args_p,		"WriteString" },		// pfnWriteString
	{ mFALSE,  23,	api_caller_void_args_i,		"WriteEntity" },		// pfnWriteEntity
	{ mFALSE,  9,	api_caller_void_args_p,		"CVarRegister" },		// pfnCVarRegister
	{ mFALSE,  21,	api_caller_float_args_p,	"CVarGetFloat" },		// pfnCVarGetFloat
	{ mFALSE,  9,	api_caller_ptr_args_p,		"CVarGetString" },		// pfnCVarGetString
	{ mFALSE,  10,	api_caller_void_args_pf,	"CVarSetFloat" },		// pfnCVarSetFloat
	{ mFALSE,  9,	api_caller_void_args_2p,	"CVarSetString" },		// pfnCVarSetString
	{ mFALSE,  15,	api_caller_void_args_ipV,	"AlertMessage" },		// pfnAlertMessage
	{ mFALSE,  17,	api_caller_void_args_2pV,	"EngineFprintf" },		// pfnEngineFprintf
	{ mFALSE,  14,	api_caller_ptr_args_pi,		"PvAllocEntPrivateData" },	// pfnPvAllocEntPrivateData
	{ mFALSE,  9,	api_caller_ptr_args_p,		"PvEntPrivateData" },		// pfnPvEntPrivateData
	{ mFALSE,  9,	api_caller_void_args_p,		"FreeEntPrivateData" },		// pfnFreeEntPrivateData
	{ mFALSE,  9,	api_caller_ptr_args_i,		"SzFromIndex" },		// pfnSzFromIndex
	{ mFALSE,  10,	api_caller_int_args_p,		"AllocString" },		// pfnAllocString
	{ mFALSE,  9,	api_caller_ptr_args_p,		"GetVarsOfEnt" },		// pfnGetVarsOfEnt
	{ mFALSE,  14,	api_caller_ptr_args_i,		"PEntityOfEntOffset" },		// pfnPEntityOfEntOffset
	{ mFALSE,  19,	api_caller_int_args_p,		"EntOffsetOfPEntity" },		// pfnEntOffsetOfPEntity
	{ mFALSE,  14,	api_caller_int_args_p,		"IndexOfEdict" },		// pfnIndexOfEdict
	{ mFALSE,  17,	api_caller_ptr_args_i,		"PEntityOfEntIndex" },		// pfnPEntityOfEntIndex
	{ mFALSE,  9,	api_caller_ptr_args_p,		"FindEntityByVars" },		// pfnFindEntityByVars
	{ mFALSE,  14,	api_caller_ptr_args_p,		"GetModelPtr" },		// pfnGetModelPtr
	{ mFALSE,  9,	api_caller_int_args_pi,		"RegUserMsg" },			// pfnRegUserMsg
	{ mFALSE,  9,	api_caller_void_args_pf,	"AnimationAutomove" },		// pfnAnimationAutomove
	{ mFALSE,  9,	api_caller_void_args_pi2p,	"GetBonePosition" },		// pfnGetBonePosition
	{ mFALSE,  9,	api_caller_uint_args_p,		"FunctionFromName" },		// pfnFunctionFromName
	{ mFALSE,  9,	api_caller_ptr_args_ui,		"NameForFunction" },		// pfnNameForFunction
	{ mFALSE,  9,	api_caller_void_args_pip,	"ClientPrintf" },		// pfnClientPrintf
	{ mFALSE,  9,	api_caller_void_args_p,		"ServerPrint" },		// pfnServerPrint
	{ mFALSE,  13,	api_caller_ptr_args_void,	"Cmd_Args" },			// pfnCmd_Args
	{ mFALSE,  13,	api_caller_ptr_args_i,		"Cmd_Argv" },			// pfnCmd_Argv
	{ mFALSE,  13,	api_caller_int_args_void,	"Cmd_Argc" },			// pfnCmd_Argc
	{ mFALSE,  9,	api_caller_void_args_pi2p,	"GetAttachment" },		// pfnGetAttachment
	{ mFALSE,  9,	api_caller_void_args_p,		"CRC32_Init" },			// pfnCRC32_Init
	{ mFALSE,  9,	api_caller_void_args_2pi,	"CRC32_ProcessBuffer" },	// pfnCRC32_ProcessBuffer
	{ mFALSE,  9,	api_caller_void_args_puc,	"CRC32_ProcessByte" },		// pfnCRC32_ProcessByte
	{ mFALSE,  9,	api_caller_ulong_args_ul,	"CRC32_Final" },		// pfnCRC32_Final
	{ mFALSE,  16,	api_caller_int_args_2i,		"RandomLong" },			// pfnRandomLong
	{ mFALSE,  14,	api_caller_float_args_2f,	"RandomFloat" },		// pfnRandomFloat		// CS: when firing
	{ mFALSE,  14,	api_caller_void_args_2p,	"SetView" },			// pfnSetView
	{ mFALSE,  9,	api_caller_float_args_void,	"Time" },			// pfnTime
	{ mFALSE,  9,	api_caller_void_args_p2f,	"CrosshairAngle" },		// pfnCrosshairAngle
	{ mFALSE,  10,	api_caller_ptr_args_2p,		"LoadFileForMe" },		// pfnLoadFileForMe
	{ mFALSE,  10,	api_caller_void_args_p,		"FreeFile" },			// pfnFreeFile
	{ mFALSE,  9,	api_caller_void_args_p,		"EndSection" },			// pfnEndSection
	{ mFALSE,  9,	api_caller_int_args_3p,		"CompareFileTime" },		// pfnCompareFileTime
	{ mFALSE,  9,	api_caller_void_args_p,		"GetGameDir" },			// pfnGetGameDir
	{ mFALSE,  9,	api_caller_void_args_p,		"Cvar_RegisterVariable" },	// pfnCvar_RegisterVariable
	{ mFALSE,  9,	api_caller_void_args_p4i,	"FadeClientVolume" },		// pfnFadeClientVolume
	{ mFALSE,  14,	api_caller_void_args_pf,	"SetClientMaxspeed" },		// pfnSetClientMaxspeed
	{ mFALSE,  9,	api_caller_ptr_args_p,		"CreateFakeClient" },		// pfnCreateFakeClient
	{ mFALSE,  9,	api_caller_void_args_2p3fus2uc,	"RunPlayerMove" },		// pfnRunPlayerMove
	{ mFALSE,  9,	api_caller_int_args_void,	"NumberOfEntities" },		// pfnNumberOfEntities
	{ mFALSE,  17,	api_caller_ptr_args_p,		"GetInfoKeyBuffer" },		// pfnGetInfoKeyBuffer
	{ mFALSE,  13,	api_caller_ptr_args_2p,		"InfoKeyValue" },		// pfnInfoKeyValue
	{ mFALSE,  9,	api_caller_void_args_3p,	"SetKeyValue" },		// pfnSetKeyValue
	{ mFALSE,  12,	api_caller_void_args_i3p,	"SetClientKeyValue" },		// pfnSetClientKeyValue
	{ mFALSE,  9,	api_caller_int_args_p,		"IsMapValid" },			// pfnIsMapValid
	{ mFALSE,  9,	api_caller_void_args_p3i,	"StaticDecal" },		// pfnStaticDecal
	{ mFALSE,  9,	api_caller_int_args_p,		"PrecacheGeneric" },		// pfnPrecacheGeneric
	{ mFALSE,  10,	api_caller_int_args_p,		"GetPlayerUserId" },		// pfnGetPlayerUserId
	{ mFALSE,  9,	api_caller_void_args_pip2f4i2p,	"BuildSoundMsg" },		// pfnBuildSoundMsg
	{ mFALSE,  9,	api_caller_int_args_void,	"IsDedicatedServer" },		// pfnIsDedicatedServer
	{ mFALSE,  9,	api_caller_ptr_args_p,		"CVarGetPointer" },		// pfnCVarGetPointer
	{ mFALSE,  9,	api_caller_uint_args_p,		"GetPlayerWONId" },		// pfnGetPlayerWONId
	{ mFALSE,  9,	api_caller_void_args_2p,	"Info_RemoveKey" },		// pfnInfo_RemoveKey
	{ mFALSE,  15,	api_caller_ptr_args_2p,		"GetPhysicsKeyValue" },		// pfnGetPhysicsKeyValue
	{ mFALSE,  14,	api_caller_void_args_3p,	"SetPhysicsKeyValue" },		// pfnSetPhysicsKeyValue
	{ mFALSE,  15,	api_caller_ptr_args_p,		"GetPhysicsInfoString" },	// pfnGetPhysicsInfoString
	{ mFALSE,  13,	api_caller_ushort_args_ip,	"PrecacheEvent" },		// pfnPrecacheEvent
	{ mFALSE,  9,	api_caller_void_args_ipusf2p2f4i,"PlaybackEvent" },		// pfnPlaybackEvent
	{ mFALSE,  31,	api_caller_ptr_args_p,		"SetFatPVS" },			// pfnSetFatPVS
	{ mFALSE,  31,	api_caller_ptr_args_p,		"SetFatPAS" },			// pfnSetFatPAS
	{ mFALSE,  50,	api_caller_int_args_2p,		"CheckVisibility" },		// pfnCheckVisibility
	{ mFALSE,  37,	api_caller_void_args_2p,	"DeltaSetField" },		// pfnDeltaSetField
	{ mFALSE,  38,	api_caller_void_args_2p,	"DeltaUnsetField" },		// pfnDeltaUnsetField
	{ mFALSE,  9,	api_caller_void_args_2p,	"DeltaAddEncoder" },		// pfnDeltaAddEncoder
	{ mFALSE,  45,	api_caller_int_args_void,	"GetCurrentPlayer" },		// pfnGetCurrentPlayer
	{ mFALSE,  14,	api_caller_int_args_p,		"CanSkipPlayer" },		// pfnCanSkipPlayer
	{ mFALSE,  9,	api_caller_int_args_2p,		"DeltaFindField" },		// pfnDeltaFindField
	{ mFALSE,  37,	api_caller_void_args_pi,	"DeltaSetFieldByIndex" },	// pfnDeltaSetFieldByIndex
	{ mFALSE,  38,	api_caller_void_args_pi,	"DeltaUnsetFieldByIndex" },	// pfnDeltaUnsetFieldByIndex
	{ mFALSE,  9,	api_caller_void_args_2i,	"SetGroupMask" },		// pfnSetGroupMask
	{ mFALSE,  9,	api_caller_int_args_ip,		"engCreateInstancedBaseline" },	// pfnCreateInstancedBaseline		// d'oh, CreateInstancedBaseline in dllapi too
	{ mFALSE,  9,	api_caller_void_args_2p,	"Cvar_DirectSet" },		// pfnCvar_DirectSet
	{ mFALSE,  9,	api_caller_void_args_i3p,	"ForceUnmodified" },		// pfnForceUnmodified
	{ mFALSE,  9,	api_caller_void_args_3p,	"GetPlayerStats" },		// pfnGetPlayerStats
	{ mFALSE,  3,	api_caller_void_args_2p,	"AddServerCommand" },		// pfnAddServerCommand
	// Added in SDK 2.2:
	{ mFALSE,  9,	api_caller_int_args_2i,		"Voice_GetClientListening" },	// Voice_GetClientListening
	{ mFALSE,  9,	api_caller_int_args_3i,		"Voice_SetClientListening" },	// Voice_SetClientListening
	// Added for HL 1109 (no SDK update):
	{ mFALSE,  9,	api_caller_ptr_args_p,		"GetPlayerAuthId" },		// pfnGetPlayerAuthId
	// Added 2003/11/10 (no SDK update):
	{ mFALSE,  30,	api_caller_ptr_args_2p,		"SequenceGet" },		// pfnSequenceGet
	{ mFALSE,  30,	api_caller_ptr_args_pip,	"SequencePickSentence" },	// pfnSequencePickSentence
	{ mFALSE,  30,	api_caller_int_args_p,		"GetFileSize" },		// pfnGetFileSize
	{ mFALSE,  30,	api_caller_uint_args_p,		"GetApproxWavePlayLen" },	// pfnGetApproxWavePlayLen
	{ mFALSE,  30,	api_caller_int_args_void,	"IsCareerMatch" },		// pfnIsCareerMatch
	{ mFALSE,  30,	api_caller_int_args_p,		"GetLocalizedStringLength" },	// pfnGetLocalizedStringLength
	{ mFALSE,  30,	api_caller_void_args_i,		"RegisterTutorMessageShown" },	// pfnRegisterTutorMessageShown
	{ mFALSE,  30,	api_caller_int_args_i,		"GetTimesTutorMessageShown" },	// pfnGetTimesTutorMessageShown
	{ mFALSE,  30,	api_caller_void_args_pi,	"ProcessTutorMessageDecayBuffer" },	// pfnProcessTutorMessageDecayBuffer
	{ mFALSE,  30,	api_caller_void_args_pi,	"ConstructTutorMessageDecayBuffer" },	// pfnConstructTutorMessageDecayBuffer
	{ mFALSE,  9,	api_caller_void_args_void,	"ResetTutorMessageDecayData" },	// pfnResetTutorMessageDecayData
	// Added 2005/08/11 (no SDK update):
	{ mFALSE,  3,	api_caller_void_args_2p,	"QueryClientCvarValue" },	// pfnQueryClientCvarValue
	// Added 2005/11/21 (no SDK update):
	{ mFALSE,  3,	api_caller_void_args_2pi,	"QueryClientCvarValue2" },	// pfnQueryClientCvarValue2
	// Added 2009-06-17 (no SDK update):
	{ mFALSE,  8,	api_caller_int_args_2p,		"EngCheckParm" },		// pfnEngCheckParm
	// end
	{ mFALSE,  0,   nullptr, nullptr },
};
