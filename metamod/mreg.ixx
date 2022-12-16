export module mreg;

export import cvardef;

export import types_meta;
export import new_baseclass;

// Number of entries to add to reglists when they need to grow.  Typically
// more cvars than commands, so we grow them at different increments.
export inline constexpr auto REG_CMD_GROWSIZE = 32;
export inline constexpr auto REG_CVAR_GROWSIZE = 64;

// Width required to printf a Reg*List index number, for show() functions.
// This used to correspond to the number of digits in MAX_REG, which was a
// fixed, compile-time limit.  However, now that the reg lists are grown
// dynamically, this has less strong correspondance to list sizes.  So for
// the moment, it reflects what one might normally expect to be the max
// width needed to print an index number; 4 allows 9999 (which is a damn
// lot, if you ask me).
export inline constexpr auto WIDTH_MAX_REG = 4;

// Max number of registered user msgs we can manage.
export inline constexpr auto MAX_REG_MSGS = 256;

// Max number of clients on server
export inline constexpr auto MAX_CLIENTS_CONNECTED = 32;

// Flags to indicate if given cvar or func is part of a loaded plugin.
export enum REG_STATUS
{
	RG_INVALID,
	RG_VALID,
};

// Pointer to function registered by AddServerCommand.
export using REG_CMD_FN = void (*) (void);


// An individual registered function/command.
export class MRegCmd : public class_metamod_new
{
	friend class MRegCmdList;
private:
	// data:
	int index;			// 1-based
public:
	char *name;			// space is malloc'd
	REG_CMD_FN pfnCmd;		// pointer to the function
	int plugid;			// index id of corresponding plugin
	REG_STATUS status;		// whether corresponding plugin is loaded
	// functions:
	void init(int idx);	// init values, as not using constructors
	mBOOL call(void);	// try to call the function
};


// A list of registered commands.
export class MRegCmdList : public class_metamod_new
{
private:
	// data:
	MRegCmd *mlist;			// malloc'd array of registered commands
	int size;			// current size of list
	int endlist;			// index of last used entry

public:
	// constructor:
	MRegCmdList(void);
	// Private; to satisfy -Weffc++ "has pointer data members but does
	// not override" copy/assignment constructor.
	// LUNA: C++11 - use "= delete" to invalidate any function.
	MRegCmdList &operator=(const MRegCmdList &src) = delete;
	MRegCmdList(const MRegCmdList &src) = delete;

	// functions:
	MRegCmd *find(const char *findname);	// find by MRegCmd->name
	MRegCmd *add(const char *addname);
	void disable(int plugin_id);		// change status to Invalid
	void show(void);			// list all funcs to console
	void show(int plugin_id);		// list given plugin's funcs to console
};



// An individual registered cvar.
export class MRegCvar : public class_metamod_new
{
	friend class MRegCvarList;
private:
	// data:
	int index;				// 1-based
public:
	cvar_t *data;				// actual cvar structure, malloc'd
	int plugid;				// index id of corresponding plugin
	REG_STATUS status;			// whether corresponding plugin is loaded
	// functions:
	void init(int idx);		// init values, as not using constructors
	mBOOL set(cvar_t *src);
};


// A list of registered cvars.
export class MRegCvarList : public class_metamod_new
{
private:
	// data:
	MRegCvar *vlist;		// malloc'd array of registered cvars
	int size;			// size of list, ie MAX_REG_CVARS
	int endlist;			// index of last used entry

public:
	// constructor:
	MRegCvarList(void);
	// Private; to satisfy -Weffc++ "has pointer data members but does
	// not override" copy/assignment constructor.
	// LUNA: C++11 - use "= delete" to invalidate any function.
	MRegCvarList &operator=(const MRegCvarList &src) = delete;
	MRegCvarList(const MRegCvarList &src) = delete;

	// functions:
	MRegCvar *add(const char *addname);
	MRegCvar *find(const char *findname);	// find by MRegCvar->data.name
	void disable(int plugin_id);		// change status to Invalid
	void show(void);			// list all cvars to console
	void show(int plugin_id);		// list given plugin's cvars to console
};



// An individual registered user msg, from gamedll.
export class MRegMsg : public class_metamod_new 
{
	friend class MRegMsgList;
private:
	// data:
	int index;				// 1-based
public:
	const char *name;		// name, assumed constant string in gamedll
	int msgid;				// msgid, assigned by engine
	int size;				// size, if given by gamedll
};


// A list of registered user msgs.
export class MRegMsgList : public class_metamod_new
{
private:
	// data:
	MRegMsg mlist[MAX_REG_MSGS];	// array of registered msgs
	int size;						// size of list, ie MAX_REG_MSGS
	int endlist;					// index of last used entry

public:
	// constructor:
	MRegMsgList(void);

	// functions:
	MRegMsg *add(const char *addname, int addmsgid, int addsize);
	MRegMsg *find(const char *findname);
	MRegMsg *find(int findmsgid);
	void show(void);						// list all msgs to console
};
