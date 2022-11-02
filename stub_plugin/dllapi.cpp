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

inline DLL_FUNCTIONS gFunctionTable =
{
	.pfnGameInit = nullptr,
	.pfnSpawn = nullptr,
	.pfnThink = nullptr,
	.pfnUse = nullptr,
	.pfnTouch = nullptr,
	.pfnBlocked = nullptr,
	.pfnKeyValue = nullptr,
	.pfnSave = nullptr,
	.pfnRestore = nullptr,
	.pfnSetAbsBox = nullptr,

	.pfnSaveWriteFields = nullptr,
	.pfnSaveReadFields = nullptr,

	.pfnSaveGlobalState = nullptr,
	.pfnRestoreGlobalState = nullptr,
	.pfnResetGlobalState = nullptr,

	.pfnClientConnect = nullptr,
	.pfnClientDisconnect = nullptr,
	.pfnClientKill = nullptr,
	.pfnClientPutInServer = nullptr,
	.pfnClientCommand = nullptr,
	.pfnClientUserInfoChanged = nullptr,
	.pfnServerActivate = nullptr,
	.pfnServerDeactivate = nullptr,

	.pfnPlayerPreThink = nullptr,
	.pfnPlayerPostThink = nullptr,

	.pfnStartFrame = nullptr,
	.pfnParmsNewLevel = nullptr,
	.pfnParmsChangeLevel = nullptr,

	.pfnGetGameDescription = nullptr,
	.pfnPlayerCustomization = nullptr,

	.pfnSpectatorConnect = nullptr,
	.pfnSpectatorDisconnect = nullptr,
	.pfnSpectatorThink = nullptr,

	.pfnSys_Error = nullptr,

	.pfnPM_Move = nullptr,
	.pfnPM_Init = nullptr,
	.pfnPM_FindTextureType = nullptr,

	.pfnSetupVisibility = nullptr,
	.pfnUpdateClientData = nullptr,
	.pfnAddToFullPack = nullptr,
	.pfnCreateBaseline = nullptr,
	.pfnRegisterEncoders = nullptr,
	.pfnGetWeaponData = nullptr,
	.pfnCmdStart = nullptr,
	.pfnCmdEnd = nullptr,
	.pfnConnectionlessPacket = nullptr,
	.pfnGetHullBounds = nullptr,
	.pfnCreateInstancedBaselines = nullptr,
	.pfnInconsistentFile = nullptr,
	.pfnAllowLagCompensation = nullptr,
};

int GetEntityAPI2(DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion) noexcept
{
	if (!pFunctionTable)
	{
		//UTIL_LogPrintf("GetEntityAPI2 called with null pFunctionTable");
		return false;
	}
	else if (*interfaceVersion != INTERFACE_VERSION)
	{
		//UTIL_LogPrintf("GetEntityAPI2 version mismatch; requested=%d ours=%d", *interfaceVersion, INTERFACE_VERSION);
		//! Tell metamod what version we had, so it can figure out who is out of date.
		*interfaceVersion = INTERFACE_VERSION;
		return false;
	}

	memcpy(pFunctionTable, &gFunctionTable, sizeof(DLL_FUNCTIONS));
	return true;
}
