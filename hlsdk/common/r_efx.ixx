export module r_efx;

// particle_t
export import particledef;

// BEAM
export import beamdef;

// dlight_t
export import dlight;

// cl_entity_t
export import cl_entity;

export import pmtrace;

// FOR REFERENCE, These are the built-in tracer colors.  Note, color 4 is the one
//  that uses the tracerred/tracergreen/tracerblue and traceralpha cvar settings
export inline constexpr color24 gTracerColors[] =
{
	{ 255, 255, 255 },		// White
	{ 255, 0, 0 },			// Red
	{ 0, 255, 0 },			// Green
	{ 0, 0, 255 },			// Blue
	{ 0, 0, 0 },			// Tracer default, filled in from cvars, etc.
	{ 255, 167, 17 },		// Yellow-orange sparks
	{ 255, 130, 90 },		// Yellowish streaks (garg)
	{ 55, 60, 144 },		// Blue egon streak
	{ 255, 130, 90 },		// More Yellowish streaks (garg)
	{ 255, 140, 90 },		// More Yellowish streaks (garg)
	{ 200, 130, 90 },		// More red streaks (garg)
	{ 255, 120, 70 },		// Darker red streaks (garg)
};

// Temporary entity array
export inline constexpr auto TENTPRIORITY_LOW = 0;
export inline constexpr auto TENTPRIORITY_HIGH = 1;

// TEMPENTITY flags
export inline constexpr auto FTENT_NONE = 0x00000000;
export inline constexpr auto FTENT_SINEWAVE = 0x00000001;
export inline constexpr auto FTENT_GRAVITY = 0x00000002;
export inline constexpr auto FTENT_ROTATE = 0x00000004;
export inline constexpr auto FTENT_SLOWGRAVITY = 0x00000008;
export inline constexpr auto FTENT_SMOKETRAIL = 0x00000010;
export inline constexpr auto FTENT_COLLIDEWORLD = 0x00000020;
export inline constexpr auto FTENT_FLICKER = 0x00000040;
export inline constexpr auto FTENT_FADEOUT = 0x00000080;
export inline constexpr auto FTENT_SPRANIMATE = 0x00000100;
export inline constexpr auto FTENT_HITSOUND = 0x00000200;
export inline constexpr auto FTENT_SPIRAL = 0x00000400;
export inline constexpr auto FTENT_SPRCYCLE = 0x00000800;
export inline constexpr auto FTENT_COLLIDEALL = 0x00001000; // will collide with world and slideboxes
export inline constexpr auto FTENT_PERSIST = 0x00002000; // tent is not removed when unable to draw 
export inline constexpr auto FTENT_COLLIDEKILL = 0x00004000; // tent is removed upon collision with anything
export inline constexpr auto FTENT_PLYRATTACHMENT = 0x00008000; // tent is attached to a player (owner)
export inline constexpr auto FTENT_SPRANIMATELOOP = 0x00010000; // animating sprite doesn't die when last frame is displayed
export inline constexpr auto FTENT_SPARKSHOWER = 0x00020000;
export inline constexpr auto FTENT_NOMODEL = 0x00040000; // Doesn't have a model, never try to draw ( it just triggers other things )
export inline constexpr auto FTENT_CLIENTCUSTOM = 0x00080000; // Must specify callback.  Callback function is responsible for killing tempent and updating fields ( unless other flags specify how to do things )

export struct tempent_s
{
	int			flags;
	float		die;
	float		frameMax;
	float		x;
	float		y;
	float		z;
	float		fadeSpeed;
	float		bounceFactor;
	int			hitSound;
	void		(*hitcallback)	(tempent_s *ent, pmtrace_t *ptr);
	void		(*callback)		(tempent_s *ent, float frametime, float currenttime);
	tempent_s *next;
	int			priority;
	short		clientIndex;	// if attached, this is the index of the client to stick to
	// if COLLIDEALL, this is the index of the client to ignore
	// TENTS with FTENT_PLYRATTACHMENT MUST set the clientindex! 

	vec3_t		tentOffset;		// if attached, client origin + tentOffset = tent origin.
	cl_entity_t	entity;

	// baseline.origin		- velocity
	// baseline.renderamt	- starting fadeout intensity
	// baseline.angles		- angle velocity
};

export using TEMPENTITY = tempent_s;

export struct efx_api_s
{
	particle_t *(*R_AllocParticle)			(void (*callback) (particle_t *particle, float frametime));
	void		(*R_BlobExplosion)			(float *org);
	void		(*R_Blood)					(float *org, float *dir, int pcolor, int speed);
	void		(*R_BloodSprite)			(float *org, int colorindex, int modelIndex, int modelIndex2, float size);
	void		(*R_BloodStream)			(float *org, float *dir, int pcolor, int speed);
	void		(*R_BreakModel)				(float *pos, float *size, float *dir, float random, float life, int count, int modelIndex, char flags);
	void		(*R_Bubbles)				(float *mins, float *maxs, float height, int modelIndex, int count, float speed);
	void		(*R_BubbleTrail)			(float *start, float *end, float height, int modelIndex, int count, float speed);
	void		(*R_BulletImpactParticles)	(float *pos);
	void		(*R_EntityParticles)		(cl_entity_t *ent);
	void		(*R_Explosion)				(float *pos, int model, float scale, float framerate, int flags);
	void		(*R_FizzEffect)				(cl_entity_t *pent, int modelIndex, int density);
	void		(*R_FireField) 				(float *org, int radius, int modelIndex, int count, int flags, float life);
	void		(*R_FlickerParticles)		(float *org);
	void		(*R_FunnelSprite)			(float *org, int modelIndex, int reverse);
	void		(*R_Implosion)				(float *end, float radius, int count, float life);
	void		(*R_LargeFunnel)			(float *org, int reverse);
	void		(*R_LavaSplash)				(float *org);
	void		(*R_MultiGunshot)			(float *org, float *dir, float *noise, int count, int decalCount, int *decalIndices);
	void		(*R_MuzzleFlash)			(float *pos1, int type);
	void		(*R_ParticleBox)			(float *mins, float *maxs, unsigned char r, unsigned char g, unsigned char b, float life);
	void		(*R_ParticleBurst)			(float *pos, int size, int color, float life);
	void		(*R_ParticleExplosion)		(float *org);
	void		(*R_ParticleExplosion2)		(float *org, int colorStart, int colorLength);
	void		(*R_ParticleLine)			(float *start, float *end, unsigned char r, unsigned char g, unsigned char b, float life);
	void		(*R_PlayerSprites)			(int client, int modelIndex, int count, int size);
	void		(*R_Projectile)				(float *origin, float *velocity, int modelIndex, int life, int owner, void (*hitcallback)(TEMPENTITY *ent, pmtrace_t *ptr));
	void		(*R_RicochetSound)			(float *pos);
	void		(*R_RicochetSprite)			(float *pos, struct model_s *pmodel, float duration, float scale);
	void		(*R_RocketFlare)			(float *pos);
	void		(*R_RocketTrail)			(float *start, float *end, int type);
	void		(*R_RunParticleEffect)		(float *org, float *dir, int color, int count);
	void		(*R_ShowLine)				(float *start, float *end);
	void		(*R_SparkEffect)			(float *pos, int count, int velocityMin, int velocityMax);
	void		(*R_SparkShower)			(float *pos);
	void		(*R_SparkStreaks)			(float *pos, int count, int velocityMin, int velocityMax);
	void		(*R_Spray)					(float *pos, float *dir, int modelIndex, int count, int speed, int spread, int rendermode);
	void		(*R_Sprite_Explode)			(TEMPENTITY *pTemp, float scale, int flags);
	void		(*R_Sprite_Smoke)			(TEMPENTITY *pTemp, float scale);
	void		(*R_Sprite_Spray)			(float *pos, float *dir, int modelIndex, int count, int speed, int iRand);
	void		(*R_Sprite_Trail)			(int type, float *start, float *end, int modelIndex, int count, float life, float size, float amplitude, int renderamt, float speed);
	void		(*R_Sprite_WallPuff)		(TEMPENTITY *pTemp, float scale);
	void		(*R_StreakSplash)			(float *pos, float *dir, int color, int count, float speed, int velocityMin, int velocityMax);
	void		(*R_TracerEffect)			(float *start, float *end);
	void		(*R_UserTracerParticle)		(float *org, float *vel, float life, int colorIndex, float length, unsigned char deathcontext, void (*deathfunc)(particle_t *particle));
	particle_t *(*R_TracerParticles)		(float *org, float *vel, float life);
	void		(*R_TeleportSplash)			(float *org);
	void		(*R_TempSphereModel)		(float *pos, float speed, float life, int count, int modelIndex);
	TEMPENTITY *(*R_TempModel)				(float *pos, float *dir, float *angles, float life, int modelIndex, int soundtype);
	TEMPENTITY *(*R_DefaultSprite)			(float *pos, int spriteIndex, float framerate);
	TEMPENTITY *(*R_TempSprite)				(float *pos, float *dir, float scale, int modelIndex, int rendermode, int renderfx, float a, float life, int flags);
	int			(*Draw_DecalIndex)			(int id);
	int			(*Draw_DecalIndexFromName)	(char *name);
	void		(*R_DecalShoot)				(int textureIndex, int entity, int modelIndex, float *position, int flags);
	void		(*R_AttachTentToPlayer)		(int client, int modelIndex, float zoffset, float life);
	void		(*R_KillAttachedTents)		(int client);
	BEAM*		(*R_BeamCirclePoints)		(int type, float *start, float *end, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b);
	BEAM*		(*R_BeamEntPoint)			(int startEnt, float *end, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b);
	BEAM*		(*R_BeamEnts)				(int startEnt, int endEnt, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b);
	BEAM*		(*R_BeamFollow)				(int startEnt, int modelIndex, float life, float width, float r, float g, float b, float brightness);
	void		(*R_BeamKill)				(int deadEntity);
	BEAM*		(*R_BeamLightning)			(float *start, float *end, int modelIndex, float life, float width, float amplitude, float brightness, float speed);
	BEAM*		(*R_BeamPoints)				(float *start, float *end, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b);
	BEAM*		(*R_BeamRing)				(int startEnt, int endEnt, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b);
	dlight_t*	(*CL_AllocDlight)			(int key);
	dlight_t*	(*CL_AllocElight)			(int key);
	TEMPENTITY*	(*CL_TempEntAlloc)			(float *org, model_t *model);
	TEMPENTITY*	(*CL_TempEntAllocNoModel)	(float *org);
	TEMPENTITY*	(*CL_TempEntAllocHigh)		(float *org, model_t *model);
	TEMPENTITY*	(*CL_TentEntAllocCustom)	(float *origin, model_t *model, int high, void (*callback) (TEMPENTITY *ent, float frametime, float currenttime));
	void		(*R_GetPackedColor)			(short *packed, short color);
	short		(*R_LookupColor)			(unsigned char r, unsigned char g, unsigned char b);
	void		(*R_DecalRemoveAll)			(int textureIndex); //textureIndex points to the decal index in the array, not the actual texture index.
};

export using efx_api_t = efx_api_s;
