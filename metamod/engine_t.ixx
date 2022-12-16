export module engine_t;

export import eiface;
export import progdefs;

export import engineinfo;

export struct engine_t
{
	engine_t() noexcept = default;
	engine_t(const engine_t &) noexcept = default;
	engine_t &operator=(const engine_t &) noexcept = default;

	enginefuncs_t *funcs{};		// engine funcs
	globalvars_t *globals{};	// engine globals
	enginefuncs_t *pl_funcs{};	// "modified" eng funcs we give to plugins
	EngineInfo info{};			// some special info elements
};

export inline engine_t Engine = {};
