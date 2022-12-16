export module mplayer;

export import edict;

export import new_baseclass;
export import types_meta;

// Numbers of players limit set by the engine
export inline constexpr auto MAX_PLAYERS = 32;

// Info on an individual player
export class MPlayer : public class_metamod_new
{
private:
	mBOOL isQueried;                         // is this player currently queried for a cvar value
	char *cvarName;                          // name of the cvar if getting queried

	MPlayer(const MPlayer &) = delete;
	MPlayer &operator=(const MPlayer &) = delete;


public:
	MPlayer();
	~MPlayer();
	void        set_cvar_query(const char *cvar);            // mark this player as querying a client cvar
	void        clear_cvar_query(const char *cvar = nullptr);     // unmark this player as querying a client cvar
	const char *is_querying_cvar(void);                      // check if a player is querying a cvar. returns
	//   NULL if not or the name of the cvar
};



// A list of players. The number of max players is fixed and small enough
// to use an array.
export class MPlayerList
{
private:
	MPlayer players[MAX_PLAYERS + 1];              // array of players

public:
	void        set_player_cvar_query(const edict_t *pEntity, const char *cvar);
	void        clear_player_cvar_query(const edict_t *pEntity, const char *cvar = nullptr);
	void        clear_all_cvar_queries(void);
	const char *is_querying_cvar(const edict_t *pEntity);
};
