// vi: set ts=4 sw=4 :
// vim: set tw=75 :

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

#include <string.h>

import eiface;

inline enginefuncs_t meta_engfuncs = 
{
	nullptr,						// pfnPrecacheModel()
	nullptr,						// pfnPrecacheSound()
	nullptr,						// pfnSetModel()
	nullptr,						// pfnModelIndex()
	nullptr,						// pfnModelFrames()

	nullptr,						// pfnSetSize()
	nullptr,						// pfnChangeLevel()
	nullptr,						// pfnGetSpawnParms()
	nullptr,						// pfnSaveSpawnParms()

	nullptr,						// pfnVecToYaw()
	nullptr,						// pfnVecToAngles()
	nullptr,						// pfnMoveToOrigin()
	nullptr,						// pfnChangeYaw()
	nullptr,						// pfnChangePitch()

	nullptr,						// pfnFindEntityByString()
	nullptr,						// pfnGetEntityIllum()
	nullptr,						// pfnFindEntityInSphere()
	nullptr,						// pfnFindClientInPVS()
	nullptr,						// pfnEntitiesInPVS()

	nullptr,						// pfnMakeVectors()
	nullptr,						// pfnAngleVectors()

	nullptr,						// pfnCreateEntity()
	nullptr,						// pfnRemoveEntity()
	nullptr,						// pfnCreateNamedEntity()

	nullptr,						// pfnMakeStatic()
	nullptr,						// pfnEntIsOnFloor()
	nullptr,						// pfnDropToFloor()

	nullptr,						// pfnWalkMove()
	nullptr,						// pfnSetOrigin()

	nullptr,						// pfnEmitSound()
	nullptr,						// pfnEmitAmbientSound()

	nullptr,						// pfnTraceLine()
	nullptr,						// pfnTraceToss()
	nullptr,						// pfnTraceMonsterHull()
	nullptr,						// pfnTraceHull()
	nullptr,						// pfnTraceModel()
	nullptr,						// pfnTraceTexture()
	nullptr,						// pfnTraceSphere()
	nullptr,						// pfnGetAimVector()

	nullptr,						// pfnServerCommand()
	nullptr,						// pfnServerExecute()
	nullptr,						// pfnClientCommand()

	nullptr,						// pfnParticleEffect()
	nullptr,						// pfnLightStyle()
	nullptr,						// pfnDecalIndex()
	nullptr,						// pfnPointContents()

	nullptr,						// pfnMessageBegin()
	nullptr,						// pfnMessageEnd()

	nullptr,						// pfnWriteByte()
	nullptr,						// pfnWriteChar()
	nullptr,						// pfnWriteShort()
	nullptr,						// pfnWriteLong()
	nullptr,						// pfnWriteAngle()
	nullptr,						// pfnWriteCoord()
	nullptr,						// pfnWriteString()
	nullptr,						// pfnWriteEntity()

	nullptr,						// pfnCVarRegister()
	nullptr,						// pfnCVarGetFloat()
	nullptr,						// pfnCVarGetString()
	nullptr,						// pfnCVarSetFloat()
	nullptr,						// pfnCVarSetString()

	nullptr,						// pfnAlertMessage()
	nullptr,						// pfnEngineFprintf()

	nullptr,						// pfnPvAllocEntPrivateData()
	nullptr,						// pfnPvEntPrivateData()
	nullptr,						// pfnFreeEntPrivateData()

	nullptr,						// pfnSzFromIndex()
	nullptr,						// pfnAllocString()

	nullptr, 						// pfnGetVarsOfEnt()
	nullptr,						// pfnPEntityOfEntOffset()
	nullptr,						// pfnEntOffsetOfPEntity()
	nullptr,						// pfnIndexOfEdict()
	nullptr,						// pfnPEntityOfEntIndex()
	nullptr,						// pfnFindEntityByVars()
	nullptr,						// pfnGetModelPtr()

	nullptr,						// pfnRegUserMsg()

	nullptr,						// pfnAnimationAutomove()
	nullptr,						// pfnGetBonePosition()

	nullptr,						// pfnFunctionFromName()
	nullptr,						// pfnNameForFunction()

	nullptr,						// pfnClientPrintf()
	nullptr,						// pfnServerPrint()

	nullptr,						// pfnCmd_Args()
	nullptr,						// pfnCmd_Argv()
	nullptr,						// pfnCmd_Argc()

	nullptr,						// pfnGetAttachment()

	nullptr,						// pfnCRC32_Init()
	nullptr,						// pfnCRC32_ProcessBuffer()
	nullptr,						// pfnCRC32_ProcessByte()
	nullptr,						// pfnCRC32_Final()

	nullptr,						// pfnRandomLong()
	nullptr,						// pfnRandomFloat()

	nullptr,						// pfnSetView()
	nullptr,						// pfnTime()
	nullptr,						// pfnCrosshairAngle()

	nullptr,						// pfnLoadFileForMe()
	nullptr,						// pfnFreeFile()

	nullptr,						// pfnEndSection()
	nullptr,						// pfnCompareFileTime()
	nullptr,						// pfnGetGameDir()
	nullptr,						// pfnCvar_RegisterVariable()
	nullptr,						// pfnFadeClientVolume()
	nullptr,						// pfnSetClientMaxspeed()
	nullptr,						// pfnCreateFakeClient()
	nullptr,						// pfnRunPlayerMove()
	nullptr,						// pfnNumberOfEntities()

	nullptr,						// pfnGetInfoKeyBuffer()
	nullptr,						// pfnInfoKeyValue()
	nullptr,						// pfnSetKeyValue()
	nullptr,						// pfnSetClientKeyValue()

	nullptr,						// pfnIsMapValid()
	nullptr,						// pfnStaticDecal()
	nullptr,						// pfnPrecacheGeneric()
	nullptr, 						// pfnGetPlayerUserId()
	nullptr,						// pfnBuildSoundMsg()
	nullptr,						// pfnIsDedicatedServer()
	nullptr,						// pfnCVarGetPointer()
	nullptr,						// pfnGetPlayerWONId()

	nullptr,						// pfnInfo_RemoveKey()
	nullptr,						// pfnGetPhysicsKeyValue()
	nullptr,						// pfnSetPhysicsKeyValue()
	nullptr,						// pfnGetPhysicsInfoString()
	nullptr,						// pfnPrecacheEvent()
	nullptr,						// pfnPlaybackEvent()

	nullptr,						// pfnSetFatPVS()
	nullptr,						// pfnSetFatPAS()

	nullptr,						// pfnCheckVisibility()

	nullptr,						// pfnDeltaSetField()
	nullptr,						// pfnDeltaUnsetField()
	nullptr,						// pfnDeltaAddEncoder()
	nullptr,						// pfnGetCurrentPlayer()
	nullptr,						// pfnCanSkipPlayer()
	nullptr,						// pfnDeltaFindField()
	nullptr,						// pfnDeltaSetFieldByIndex()
	nullptr,						// pfnDeltaUnsetFieldByIndex()

	nullptr,						// pfnSetGroupMask()

	nullptr,						// pfnCreateInstancedBaseline()
	nullptr,						// pfnCvar_DirectSet()

	nullptr,						// pfnForceUnmodified()

	nullptr,						// pfnGetPlayerStats()

	nullptr,						// pfnAddServerCommand()

	// Added in SDK 2.2:
	nullptr,						// pfnVoice_GetClientListening()
	nullptr,						// pfnVoice_SetClientListening()

	// Added for HL 1109 (no SDK update):
	nullptr,						// pfnGetPlayerAuthId()

	// Added 2003/11/10 (no SDK update):
	nullptr,						// pfnSequenceGet()
	nullptr,						// pfnSequencePickSentence()
	nullptr,						// pfnGetFileSize()
	nullptr,						// pfnGetApproxWavePlayLen()
	nullptr,						// pfnIsCareerMatch()
	nullptr,						// pfnGetLocalizedStringLength()
	nullptr,						// pfnRegisterTutorMessageShown()
	nullptr,						// pfnGetTimesTutorMessageShown()
	nullptr,						// pfnProcessTutorMessageDecayBuffer()
	nullptr,						// pfnConstructTutorMessageDecayBuffer()
	nullptr,						// pfnResetTutorMessageDecayData()

	// Added Added 2005-08-11 (no SDK update)
	nullptr,						// pfnQueryClientCvarValue()
	// Added Added 2005-11-22 (no SDK update)
	nullptr,						// pfnQueryClientCvarValue2()
	// Added 2009-06-17 (no SDK update)
	nullptr,						// pfnEngCheckParm()
};

int GetEngineFunctions(enginefuncs_t *pengfuncsFromEngine, int *interfaceVersion) noexcept
{
	if (!pengfuncsFromEngine)
	{
		//UTIL_LogPrintf("GetEngineFunctions called with null pengfuncsFromEngine");
		return false;
	}
	else if (*interfaceVersion != 138)
	{
		//UTIL_LogPrintf("GetEngineFunctions version mismatch; requested=%d ours=%d", *interfaceVersion, ENGINE_INTERFACE_VERSION);
		// Tell metamod what version we had, so it can figure out who is out of date.
		*interfaceVersion = 138;
		return false;
	}

	memcpy(pengfuncsFromEngine, &meta_engfuncs, sizeof(enginefuncs_t));
	return true;
}
