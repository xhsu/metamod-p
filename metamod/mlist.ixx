export module mlist;

export import new_baseclass;
export import mplugin;

// Max number of plugins we can manage.  This is an arbitrary, fixed number,
// for convenience.  It would probably be better to dynamically grow the
// list as needed, but we do this for now.
export inline constexpr auto MAX_PLUGINS = 50;
// Width required to printf above MAX, for show() functions.
export inline constexpr auto WIDTH_MAX_PLUGINS = 2;


// A list of plugins.
export class MPluginList : public class_metamod_new
{
public:
	// data:
	MPlugin plist[MAX_PLUGINS];			// array of plugins
	int size;					// size of list, ie MAX_PLUGINS
	int endlist;					// index of last used entry
	char inifile[PATH_MAX];				// full pathname

	// constructor:
	MPluginList(const char *ifile);

	// functions:
	void  reset_plugin(MPlugin *pl_find);
	MPlugin *find(int pindex);			// find by index
	MPlugin *find(const char *findpath); 	// find by pathname
	MPlugin *find(plid_t id);			// find by plid_t
	MPlugin *find(DLHANDLE handle);		// find by handle
	MPlugin *find_memloc(void *memptr);	// find by memory location
	MPlugin *find_match(const char *prefix);	// find by partial prefix match
	MPlugin *find_match(MPlugin *pmatch);	// find by platform_match()
	MPlugin *add(MPlugin *padd);

	mBOOL  found_child_plugins(int source_index);
	void  clear_source_plugin_index(int source_index);
	void  trim_list(void);

	mBOOL  ini_startup(void);			// read inifile at startup
	mBOOL  ini_refresh(void);			// re-read inifile
	mBOOL  cmd_addload(const char *args);	// load from console command
	MPlugin *plugin_addload(plid_t plid, const char *fname, PLUG_LOADTIME now); //load from plugin

	mBOOL  load(void);				// load the list, at startup
	mBOOL  refresh(PLUG_LOADTIME now);		// update from re-read inifile
	void  unpause_all(void);			// unpause any paused plugins
	void  retry_all(PLUG_LOADTIME now);		// retry any pending plugin actions
	void  show(int source_index);		// list plugins to console
	void  show(void) { show(-1); };		// list plugins to console
	void  show_client(edict_t *pEntity);		// list plugins to player client
};
