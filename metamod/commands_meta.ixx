export module commands_meta;

export import edict;

// Flags to use for meta_cmd_doplug(), to operate on existing plugins; note
// "load" operates on a non-existing plugin thus isn't included here.
export enum PLUG_CMD
{
	PC_NULL = 0,
	PC_PAUSE,		// pause the plugin
	PC_UNPAUSE,		// unpause the plugin
	PC_UNLOAD,		// unload the plugin
	PC_RELOAD,		// unload the plugin and load it again
	PC_RETRY,		// retry a failed operation (usually load/attach)
	PC_INFO,		// show all info about the plugin
	PC_CLEAR,		// remove a failed plugin from the list
	PC_FORCE_UNLOAD,	// forcibly unload the plugin
	PC_REQUIRE,		// require that this plugin is loaded/running
};

export extern "C++" void meta_register_cmdcvar() noexcept;

export extern "C++" void svr_meta(void) noexcept; // only hidden because called from outside!

export extern "C++" void cmd_meta_usage(void) noexcept;
export extern "C++" void cmd_meta_version(void) noexcept;
export extern "C++" void cmd_meta_gpl(void) noexcept;

export extern "C++" void cmd_meta_game(void) noexcept;
export extern "C++" void cmd_meta_refresh(void) noexcept;
export extern "C++" void cmd_meta_load(void) noexcept;

export extern "C++" void cmd_meta_pluginlist(void) noexcept;
export extern "C++" void cmd_meta_cmdlist(void) noexcept;
export extern "C++" void cmd_meta_cvarlist(void) noexcept;
export extern "C++" void cmd_meta_config(void) noexcept;

export extern "C++" void cmd_doplug(PLUG_CMD pcmd) noexcept;

export extern "C++" void client_meta(edict_t *pEntity) noexcept;
export extern "C++" void client_meta_usage(edict_t *pEntity) noexcept;
export extern "C++" void client_meta_version(edict_t *pEntity) noexcept;
export extern "C++" void client_meta_pluginlist(edict_t *pEntity) noexcept;
export extern "C++" void client_meta_aybabtu(edict_t *pEntity) noexcept;
