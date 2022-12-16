export module conf_meta;

export import new_baseclass;
export import types_meta;

// Max length of line in config file.
export inline constexpr auto MAX_CONF_LEN = 1024;

// Supported config value-types.
export enum cf_type_t
{
	CF_NONE = 0,
	CF_INT,
	CF_BOOL,
	CF_STR,
	CF_PATH,
#if 0
	CF_CVAR,
	CF_CMD,
#endif
};

//typedef mBOOL (*SETOPT_FN) (char *key, char *value);

export struct option_t
{
	char *name;		// option name
	cf_type_t type;	// option type
	void *dest;		// addr of destination variable, or handler function
	char *init;		// initial value, as a string, just as config file would
};

export class MConfig : public class_metamod_new
{
private:
	// data
	option_t *list;
	char *filename;
	// functions
	option_t *find(const char *lookup);
	mBOOL  set(option_t *setp, const char *value);

public:
	// contructor
	MConfig(void);
	// Private; to satisfy -Weffc++ "has pointer data members but does
	// not override" copy/assignment constructor.
	// LUNA: use '=delete' to invalidate any function.
	MConfig &operator=(const MConfig &src) = delete;
	MConfig(const MConfig &src) = delete;

	// data
	int debuglevel;		// to use for meta_debug
	char *gamedll;		// string if specified in config.ini
	char *plugins_file;	// ie metamod.ini, plugins.ini
	char *exec_cfg;		// ie metaexec.cfg, exec.cfg
	int autodetect;		// autodetection of gamedll (Metamod-All-Support patch)
	int clientmeta;         // control 'meta' client-command
	// functions
	void  init(option_t *global_options);
	mBOOL  load(const char *filename);
	mBOOL  set(const char *key, const char *value);
	void  show(void);
};