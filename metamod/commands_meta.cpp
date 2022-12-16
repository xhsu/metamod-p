// vi: set ts=4 sw=4 :
// vim: set tw=75 :

// commands_meta.cpp - implementation of various console commands

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

#include <fmt/core.h>

import <cstring>;

import metamod;
import cvardef;
import commands_meta;


#ifdef META_PERFMON

long double total_tsc=0;
unsigned long long count_tsc=0;
unsigned long long active_tsc=0;
unsigned long long min_tsc=0;

void cmd_meta_tsc(void) {
	if(!count_tsc)
		return;
	
	g_engfuncs.pfnServerPrint(" ");
	g_engfuncs.pfnServerPrint(" count_tsc: %.0f", (double)count_tsc);
	g_engfuncs.pfnServerPrint(" mean_tsc: %.1f", (double)(total_tsc / count_tsc));
	g_engfuncs.pfnServerPrint(" min_tsc: %.0f", (double)min_tsc);
}

void cmd_meta_reset_tsc(void) {
	total_tsc=0;
	count_tsc=0;
	min_tsc=0;
}
#endif /*META_PERFMON*/

inline cvar_t meta_debug = { "meta_debug", "0", FCVAR_EXTDLL, 0, nullptr };

// Register commands and cvars.
void meta_register_cmdcvar() noexcept
{
	g_engfuncs.pfnCVarRegister(&meta_debug);
	g_engfuncs.pfnCVarRegister(&meta_version);

	g_engfuncs.pfnAddServerCommand("meta", svr_meta);
}

// Parse "meta" console command.
void svr_meta(void) noexcept
{
	const char *cmd = g_engfuncs.pfnCmd_Argv(1);

	// arguments: none
	if(!_stricmp(cmd, "version"))
		cmd_meta_version();
	else if(!_stricmp(cmd, "gpl"))
		cmd_meta_gpl();
	else if(!_stricmp(cmd, "refresh"))
		cmd_meta_refresh();
	else if(!_stricmp(cmd, "list"))
		cmd_meta_pluginlist();
	else if(!_stricmp(cmd, "cmds"))
		cmd_meta_cmdlist();
	else if(!_stricmp(cmd, "cvars"))
		cmd_meta_cvarlist();
	else if(!_stricmp(cmd, "game"))
		cmd_meta_game();
	else if(!_stricmp(cmd, "config"))
		cmd_meta_config();
	// arguments: existing plugin(s)
	else if(!_stricmp(cmd, "pause"))
		cmd_doplug(PC_PAUSE);
	else if(!_stricmp(cmd, "unpause"))
		cmd_doplug(PC_UNPAUSE);
	else if(!_stricmp(cmd, "unload"))
		cmd_doplug(PC_UNLOAD);
	else if(!_stricmp(cmd, "force_unload"))
		cmd_doplug(PC_FORCE_UNLOAD);
	else if(!_stricmp(cmd, "reload"))
		cmd_doplug(PC_RELOAD);
	else if(!_stricmp(cmd, "retry"))
		cmd_doplug(PC_RETRY);
	else if(!_stricmp(cmd, "clear"))
		cmd_doplug(PC_CLEAR);
	else if(!_stricmp(cmd, "info"))
		cmd_doplug(PC_INFO);
	else if(!_stricmp(cmd, "require"))
		cmd_doplug(PC_REQUIRE);
	// arguments: filename, description
	else if(!_stricmp(cmd, "load"))
		cmd_meta_load();
#ifdef META_PERFMON
	else if(!_stricmp(cmd, "tsc"))
		cmd_meta_tsc();
	else if(!_stricmp(cmd, "reset_tsc"))
		cmd_meta_reset_tsc();
#endif /*META_PERFMON*/
	// unrecognized
	else
	{
		g_engfuncs.pfnServerCommand(fmt::format("Unrecognized meta command: {}", cmd).c_str());
		cmd_meta_usage();
		return;
	}
}

// Parse "meta" client command.
void client_meta(edict_t *pEntity) noexcept
{
	const char *cmd = g_engfuncs.pfnCmd_Argv(1);

	// arguments: none
	if(strmatch(cmd, "version"))
		client_meta_version(pEntity);
	else if(strmatch(cmd, "list"))
		client_meta_pluginlist(pEntity);
	else if(strmatch(cmd, "aybabtu"))
		client_meta_aybabtu(pEntity);

	// unrecognized
	else
	{
		g_engfuncs.pfnClientPrintf(pEntity, print_console, fmt::format("Unrecognized meta command: {}", cmd).c_str());
		client_meta_usage(pEntity);
		return;
	}
}

// Print usage for "meta" console command.
void cmd_meta_usage(void) noexcept
{
	g_engfuncs.pfnServerPrint("usage: meta <command> [<arguments>]");
	g_engfuncs.pfnServerPrint("valid commands are:");
	g_engfuncs.pfnServerPrint("   version          - display metamod version info");
	g_engfuncs.pfnServerPrint("   game             - display gamedll info");
	g_engfuncs.pfnServerPrint("   list             - list plugins currently loaded");
	g_engfuncs.pfnServerPrint("   cmds             - list console cmds registered by plugins");
	g_engfuncs.pfnServerPrint("   cvars            - list cvars registered by plugins");
	g_engfuncs.pfnServerPrint("   refresh          - load/unload any new/deleted/updated plugins");
	g_engfuncs.pfnServerPrint("   config           - show config info loaded from config.ini");
	g_engfuncs.pfnServerPrint("   load <name>      - find and load a plugin with the given name");
	g_engfuncs.pfnServerPrint("   unload <plugin>  - unload a loaded plugin");
	g_engfuncs.pfnServerPrint("   reload <plugin>  - unload a plugin and load it again");
	g_engfuncs.pfnServerPrint("   info <plugin>    - show all information about a plugin");
	g_engfuncs.pfnServerPrint("   pause <plugin>   - pause a loaded, running plugin");
	g_engfuncs.pfnServerPrint("   unpause <plugin> - unpause a previously paused plugin");
	g_engfuncs.pfnServerPrint("   retry <plugin>   - retry a plugin that previously failed its action");
	g_engfuncs.pfnServerPrint("   clear <plugin>   - clear a failed plugin from the list");
	g_engfuncs.pfnServerPrint("   force_unload <plugin>  - forcibly unload a loaded plugin");
	g_engfuncs.pfnServerPrint("   require <plugin> - exit server if plugin not loaded/running");
}

// Print usage for "meta" client command.
void client_meta_usage(edict_t *pEntity) noexcept
{
	g_engfuncs.pfnClientPrintf(pEntity, print_console, "usage: meta <command> [<arguments>]");
	g_engfuncs.pfnClientPrintf(pEntity, print_console, "valid commands are:");
	g_engfuncs.pfnClientPrintf(pEntity, print_console, "   version          - display metamod version info");
	g_engfuncs.pfnClientPrintf(pEntity, print_console, "   list             - list plugins currently loaded");
}

// "meta aybabtu" client command.
void client_meta_aybabtu(edict_t *pEntity) noexcept
{
	g_engfuncs.pfnClientPrintf(pEntity, print_console, "All Your Base Are Belong To Us");
}

// "meta version" console command.
void cmd_meta_version(void) noexcept
{
	if(g_engfuncs.pfnCmd_Argc() != 2)
	{
		g_engfuncs.pfnServerPrint("usage: meta version");
		return;
	}

	g_engfuncs.pfnServerPrint(fmt::format("{} v{}  {} ({})", VNAME, VVERSION, VDATE, META_INTERFACE_VERSION).c_str());
	g_engfuncs.pfnServerPrint(fmt::format("by {}", VAUTHOR).c_str());
	g_engfuncs.pfnServerPrint(fmt::format("   {}", VURL).c_str());
	g_engfuncs.pfnServerPrint(fmt::format(" Patch: {} v{}", VPATCH_NAME, VPATCH_IVERSION).c_str());
	g_engfuncs.pfnServerPrint(fmt::format(" by {}", VPATCH_AUTHOR).c_str());
	g_engfuncs.pfnServerPrint(fmt::format("    {}", VPATCH_WEBSITE).c_str());
	g_engfuncs.pfnServerPrint(fmt::format("compiled: {} {} ({})", COMPILE_TIME, COMPILE_TZONE, OPT_TYPE).c_str());
}

// "meta version" client command.
void client_meta_version(edict_t *pEntity) noexcept
{
	if (g_engfuncs.pfnCmd_Argc() != 2)
	{
		g_engfuncs.pfnClientPrintf(pEntity, print_console, "usage: meta version");
		return;
	}
	g_engfuncs.pfnClientPrintf(pEntity, print_console, fmt::format("{} v{}  {} ({})", VNAME, VVERSION, VDATE, META_INTERFACE_VERSION).c_str());
	g_engfuncs.pfnClientPrintf(pEntity, print_console, fmt::format("by {}", VAUTHOR).c_str());
	g_engfuncs.pfnClientPrintf(pEntity, print_console, fmt::format("   {}", VURL).c_str());
	g_engfuncs.pfnClientPrintf(pEntity, print_console, fmt::format(" Patch: {} v{}", VPATCH_NAME, VPATCH_IVERSION).c_str());
	g_engfuncs.pfnClientPrintf(pEntity, print_console, fmt::format(" by {}", VPATCH_AUTHOR).c_str());
	g_engfuncs.pfnClientPrintf(pEntity, print_console, fmt::format("    {}", VPATCH_WEBSITE).c_str());
	g_engfuncs.pfnClientPrintf(pEntity, print_console, fmt::format("compiled: {} {} ({})", COMPILE_TIME, COMPILE_TZONE, OPT_TYPE).c_str());
	g_engfuncs.pfnClientPrintf(pEntity, print_console, fmt::format("ifvers: {}", META_INTERFACE_VERSION).c_str());
}

// "meta gpl" console command.
void cmd_meta_gpl(void) noexcept
{
	g_engfuncs.pfnServerPrint(fmt::format("%s version %s  %s", VNAME, VVERSION, VDATE).c_str());
	g_engfuncs.pfnServerPrint(fmt::format("Copyright (c) 2001-%s %s", COPYRIGHT_YEAR, VAUTHOR).c_str());
	g_engfuncs.pfnServerPrint("");
	g_engfuncs.pfnServerPrint(fmt::format("   %s is free software; you can redistribute it and/or", VNAME).c_str());
	g_engfuncs.pfnServerPrint("   modify it under the terms of the GNU General Public License");
	g_engfuncs.pfnServerPrint("   as published by the Free Software Foundation; either");
	g_engfuncs.pfnServerPrint("   version 2 of the License, or (at your option) any later");
	g_engfuncs.pfnServerPrint("   version.");
	g_engfuncs.pfnServerPrint("   ");
	g_engfuncs.pfnServerPrint(fmt::format("   %s is distributed in the hope that it will be useful,", VNAME).c_str());
	g_engfuncs.pfnServerPrint("   but WITHOUT ANY WARRANTY; without even the implied warranty");
	g_engfuncs.pfnServerPrint("   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.");
	g_engfuncs.pfnServerPrint("   See the GNU General Public License for more details.");
	g_engfuncs.pfnServerPrint("   ");
	g_engfuncs.pfnServerPrint("   You should have received a copy of the GNU General Public");
	g_engfuncs.pfnServerPrint("   License along with Metamod; if not, write to the Free");
	g_engfuncs.pfnServerPrint("   Software Foundation, Inc., 59 Temple Place, Suite 330,");
	g_engfuncs.pfnServerPrint("   Boston, MA 02111-1307  USA");
	g_engfuncs.pfnServerPrint("   ");
	g_engfuncs.pfnServerPrint("   In addition, as a special exception, the author gives");
	g_engfuncs.pfnServerPrint("   permission to link the code of this program with the");
	g_engfuncs.pfnServerPrint("   Half-Life Game Engine (\"HL Engine\") and Modified Game");
	g_engfuncs.pfnServerPrint("   Libraries (\"MODs\") developed by Valve, L.L.C (\"Valve\").");
	g_engfuncs.pfnServerPrint("   You must obey the GNU General Public License in all");
	g_engfuncs.pfnServerPrint("   respects for all of the code used other than the HL Engine");
	g_engfuncs.pfnServerPrint("   and MODs from Valve.  If you modify this file, you may");
	g_engfuncs.pfnServerPrint("   extend this exception to your version of the file, but you");
	g_engfuncs.pfnServerPrint("   are not obligated to do so.  If you do not wish to do so,");
	g_engfuncs.pfnServerPrint("   delete this exception statement from your version.");
}

// "meta game" console command.
void cmd_meta_game(void) {
	if(g_engfuncs.pfnCmd_Argc() != 2) {
		g_engfuncs.pfnServerPrint("usage: meta game");
		return;
	}
	g_engfuncs.pfnServerPrint("GameDLL info:");
	g_engfuncs.pfnServerPrint("        name: %s", GameDLL.name);
	g_engfuncs.pfnServerPrint("        desc: %s", GameDLL.desc);
	g_engfuncs.pfnServerPrint("     gamedir: %s", GameDLL.gamedir);
	g_engfuncs.pfnServerPrint("    dll file: %s", GameDLL.file);
	g_engfuncs.pfnServerPrint("dll pathname: %s", GameDLL.pathname);
	RegMsgs->show();
}

// "meta refresh" console command.
void cmd_meta_refresh(void) {
	if(g_engfuncs.pfnCmd_Argc() != 2) {
		g_engfuncs.pfnServerPrint("usage: meta refresh");
		return;
	}
	META_LOG("Refreshing the plugins on demand...");
	if(Plugins->refresh(PT_ANYTIME) != mTRUE) {
		META_LOG("Refresh failed.");
	}
}

// "meta list" console command.
void cmd_meta_pluginlist(void) {
	if(g_engfuncs.pfnCmd_Argc() != 2) {
		g_engfuncs.pfnServerPrint("usage: meta list");
		return;
	}
	Plugins->show();
}

// "meta list" client command.
void client_meta_pluginlist(edict_t *pEntity) {
	if(g_engfuncs.pfnCmd_Argc() != 2) {
		g_engfuncs.pfnClientPrintf(pEntity, print_console, "usage: meta list");
		return;
	}
	Plugins->show_client(pEntity);
}

// "meta cmds" console command.
void cmd_meta_cmdlist(void) {
	if(g_engfuncs.pfnCmd_Argc() != 2) {
		g_engfuncs.pfnServerPrint("usage: meta cmds");
		return;
	}
	RegCmds->show();
}

// "meta cvars" console command.
void cmd_meta_cvarlist(void) {
	if(g_engfuncs.pfnCmd_Argc() != 2) {
		g_engfuncs.pfnServerPrint("usage: meta cvars");
		return;
	}
	RegCvars->show();
}

// "meta config" console command.
void cmd_meta_config(void) {
	if(g_engfuncs.pfnCmd_Argc() != 2) {
		g_engfuncs.pfnServerPrint("usage: meta cvars");
		return;
	}
	Config->show();
}

// gamedir/filename
// gamedir/dlls/filename
//
// dir/mm_file
// dir/file
//
// path
// path_mm
// path_MM
// path.so, path.dll
// path_i386.so, path_i486.so, etc

// "meta load" console command.
void cmd_meta_load(void) {
	int argc;
	const char *args;
	argc=g_engfuncs.pfnCmd_Argc();
	if(argc < 3) {
		g_engfuncs.pfnServerPrint("usage: meta load <name> [<description>]");
		g_engfuncs.pfnServerPrint("   where <name> is an identifier used to locate the plugin file.");
		g_engfuncs.pfnServerPrint("   The system will look for a number of files based on this name, including:");
		g_engfuncs.pfnServerPrint("      name");
#ifdef linux
		g_engfuncs.pfnServerPrint("      name.so");
		g_engfuncs.pfnServerPrint("      name_mm.so");
		g_engfuncs.pfnServerPrint("      name_MM.so");
		g_engfuncs.pfnServerPrint("      mm_name.so");
#ifdef __x86_64__
		g_engfuncs.pfnServerPrint("      name_amd64.so");
		g_engfuncs.pfnServerPrint("      name_x86_64.so");
#else
		g_engfuncs.pfnServerPrint("      name_i386.so");
		g_engfuncs.pfnServerPrint("      name_i686.so");
#endif
#elif defined(_WIN32)
		g_engfuncs.pfnServerPrint("      name.dll");
		g_engfuncs.pfnServerPrint("      name_mm.dll");
		g_engfuncs.pfnServerPrint("      mm_name.dll");
#endif /* linux */
		g_engfuncs.pfnServerPrint("   in a number of directories, including:");
		g_engfuncs.pfnServerPrint("      <gamedir>");
		g_engfuncs.pfnServerPrint("      <gamedir>/dlls");
		g_engfuncs.pfnServerPrint("      <given path, if absolute>");
		return;
	}
	args=CMD_ARGS();
	// cmd_addload() handles all the feedback to the console..
	Plugins->cmd_addload(args);
}

// Handle various console commands that refer to a known/loaded plugin.
void cmd_doplug(PLUG_CMD pcmd) {
	int i=0, argc;
	const char *cmd, *arg;
	MPlugin *findp;

	argc=g_engfuncs.pfnCmd_Argc();
	cmd=CMD_ARGV(1);
	if(argc < 3) {
		g_engfuncs.pfnServerPrint("usage: meta %s <plugin> [<plugin> ...]", cmd);
		g_engfuncs.pfnServerPrint("   where <plugin> can be either the plugin index #");
		g_engfuncs.pfnServerPrint("   or a non-ambiguous prefix string matching name, desc, file, or logtag");
		return;
	}
	// i=2 to skip first arg, as that's the "cmd"
	for(i=2; i < argc; i++) {
		int pindex;
		char *endptr;
		
		arg=CMD_ARGV(i);
		
		// try to match plugin id first
		pindex = strtol(arg, &endptr, 10);
		if(*arg && !*endptr)
			findp=Plugins->find(pindex);
		// else try to match some string (prefix)
		else
			findp=Plugins->find_match(arg);

		// Require that:
		//  - specified plugin was found in the list of current plugins
		//  - plugin successfully loaded and began running
		// Otherwise, print error and exit.
		if(pcmd==PC_REQUIRE) {
			if(findp && findp->status >= PL_RUNNING) {
				META_DEBUG(3, ("Required plugin '%s' found loaded and running.",
						arg));
				return;
			}
			// Output to both places, because we don't want the admin
			// to miss this..
			if(!findp && meta_errno == ME_NOTUNIQ) {
				META_ERROR("Unique match for required plugin '%s' was not found!  Exiting.", arg);
				g_engfuncs.pfnServerPrint("\nERROR: Unique match for required plugin '%s' was not found!  Exiting.\n", arg);
			}
			else if(!findp) {
				META_ERROR("Required plugin '%s' was not found!  Exiting.",
						arg);
				g_engfuncs.pfnServerPrint("\nERROR: Required plugin '%s' was not found!  Exiting.\n",
						arg);
			}
			else {
				META_ERROR("Required plugin '%s' did not load successfully!  (status=%s)  Exiting.", arg, findp->str_status(ST_SIMPLE));
				g_engfuncs.pfnServerPrint("\nERROR: Required plugin '%s' did not load successfully!  (status=%s)  Exiting.\n", arg, findp->str_status(ST_SIMPLE));
			}
			// Allow chance to read the message, before any window closes.
			do_exit(1);
		}

		if(!findp) {
			if(meta_errno == ME_NOTUNIQ)
				g_engfuncs.pfnServerPrint("Couldn't find unique plugin matching '%s'", arg);
			else
				g_engfuncs.pfnServerPrint("Couldn't find plugin matching '%s'", arg);
			return;
		}

		if(pcmd==PC_PAUSE) {
			if(findp->pause())
				g_engfuncs.pfnServerPrint("Paused plugin '%s'", findp->desc);
			else
				g_engfuncs.pfnServerPrint("Pause failed for plugin '%s'", findp->desc);
		}
		else if(pcmd==PC_UNPAUSE) {
			if(findp->unpause())
				g_engfuncs.pfnServerPrint("Unpaused plugin '%s'", findp->desc);
			else
				g_engfuncs.pfnServerPrint("Unpause failed for plugin '%s'", findp->desc);
		}
		else if(pcmd==PC_UNLOAD) {
			findp->action=PA_UNLOAD;
			if(findp->unload(PT_ANYTIME, PNL_COMMAND, PNL_COMMAND)) {
				g_engfuncs.pfnServerPrint("Unloaded plugin '%s'", findp->desc);
				Plugins->show();
			}
			else if(meta_errno == ME_DELAYED)
				g_engfuncs.pfnServerPrint("Unload delayed for plugin '%s'", findp->desc);
			else
				g_engfuncs.pfnServerPrint("Unload failed for plugin '%s'", findp->desc);
		}
		else if(pcmd==PC_FORCE_UNLOAD) {
			findp->action=PA_UNLOAD;
			if(findp->unload(PT_ANYTIME, PNL_CMD_FORCED, PNL_CMD_FORCED)) {
				g_engfuncs.pfnServerPrint("Forced unload plugin '%s'", findp->desc);
				Plugins->show();
			}
			else
				g_engfuncs.pfnServerPrint("Forced unload failed for plugin '%s'", findp->desc);
		}
		else if(pcmd==PC_RELOAD) {
			findp->action=PA_RELOAD;
			if(findp->reload(PT_ANYTIME, PNL_COMMAND))
				g_engfuncs.pfnServerPrint("Reloaded plugin '%s'", findp->desc);
			else if(meta_errno == ME_DELAYED)
				g_engfuncs.pfnServerPrint("Reload delayed for plugin '%s'", findp->desc);
			else if(meta_errno == ME_NOTALLOWED)
				g_engfuncs.pfnServerPrint("Reload not allowed for plugin '%s' now, only allowed %s", findp->desc, findp->str_loadable(SL_ALLOWED));
			else
				g_engfuncs.pfnServerPrint("Reload failed for plugin '%s'", findp->desc);
		}
		else if(pcmd==PC_RETRY) {
			if(findp->retry(PT_ANYTIME, PNL_COMMAND))
				g_engfuncs.pfnServerPrint("Retry succeeded for plugin '%s'", findp->desc);
			else
				g_engfuncs.pfnServerPrint("Retry failed for plugin '%s'", findp->desc);
		}
		else if(pcmd==PC_CLEAR) {
			if(findp->clear()) {
				g_engfuncs.pfnServerPrint("Cleared failed plugin '%s' from list", findp->desc);
				Plugins->show();
			}
			else
				g_engfuncs.pfnServerPrint("Clear failed for plugin '%s'", findp->desc);
		}
		else if(pcmd==PC_INFO)
			findp->show();
		else {
			META_WARNING("Unexpected plug_cmd: %d", pcmd);
			g_engfuncs.pfnServerPrint("Command failed; see log");
		}
	}
}
