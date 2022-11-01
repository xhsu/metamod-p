export module event_api;

export import pmtrace;

export inline constexpr auto EVENT_API_VERSION = 1;

export struct event_api_s
{
	int		version;
	void	(*EV_PlaySound) (int ent, float *origin, int channel, const char *sample, float volume, float attenuation, int fFlags, int pitch);
	void	(*EV_StopSound) (int ent, int channel, const char *sample);
	int		(*EV_FindModelIndex)(const char *pmodel);
	int		(*EV_IsLocal) (int playernum);
	int		(*EV_LocalPlayerDucking) (void);
	void	(*EV_LocalPlayerViewheight) (float *);
	void	(*EV_LocalPlayerBounds) (int hull, float *mins, float *maxs);
	int		(*EV_IndexFromTrace) (pmtrace_t *pTrace);
	struct physent_s *(*EV_GetPhysent) (int idx);
	void	(*EV_SetUpPlayerPrediction) (int dopred, int bIncludeLocalClient);
	void	(*EV_PushPMStates) (void);
	void	(*EV_PopPMStates) (void);
	void	(*EV_SetSolidPlayers) (int playernum);
	void	(*EV_SetTraceHull) (int hull);
	void	(*EV_PlayerTrace) (float *start, float *end, int traceFlags, int ignore_pe, struct pmtrace_s *tr);
	void	(*EV_WeaponAnimation) (int sequence, int body);
	unsigned short (*EV_PrecacheEvent) (int type, const char *psz);
	void	(*EV_PlaybackEvent) (int flags, const struct edict_s *pInvoker, unsigned short eventindex, float delay, float *origin, float *angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2);
	const char *(*EV_TraceTexture) (int ground, float *vstart, float *vend);
	void	(*EV_StopAllSounds) (int entnum, int entchannel);
	void    (*EV_KillEvents) (int entnum, const char *eventname);
};

export using event_api_t = event_api_s;
