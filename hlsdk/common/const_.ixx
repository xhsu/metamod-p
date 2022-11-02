module;

#include <cstdint>

export module const_;

export import edict;
export import vector;

//
// Constants shared by the engine and dlls
// This header file included by engine files and DLL files.
// Most came from server.h

// edict->flags
export inline constexpr auto FL_FLY = (1 << 0);	// Changes the SV_Movestep() behavior to not need to be on ground
export inline constexpr auto FL_SWIM = (1 << 1);	// Changes the SV_Movestep() behavior to not need to be on ground (but stay in water)
export inline constexpr auto FL_CONVEYOR = (1 << 2);
export inline constexpr auto FL_CLIENT = (1 << 3);
export inline constexpr auto FL_INWATER = (1 << 4);
export inline constexpr auto FL_MONSTER = (1 << 5);
export inline constexpr auto FL_GODMODE = (1 << 6);
export inline constexpr auto FL_NOTARGET = (1 << 7);
export inline constexpr auto FL_SKIPLOCALHOST = (1 << 8);	// Don't send entity to local host, it's predicting this entity itself
export inline constexpr auto FL_ONGROUND = (1 << 9);	// At rest / on the ground
export inline constexpr auto FL_PARTIALGROUND = (1 << 10);	// not all corners are valid
export inline constexpr auto FL_WATERJUMP = (1 << 11);	// player jumping out of water
export inline constexpr auto FL_FROZEN = (1 << 12); // Player is frozen for 3rd person camera
export inline constexpr auto FL_FAKECLIENT = (1 << 13);	// JAC: fake client, simulated server side; don't send network messages to them
export inline constexpr auto FL_DUCKING = (1 << 14);	// Player flag -- Player is fully crouched
export inline constexpr auto FL_FLOAT = (1 << 15);	// Apply floating force to this entity when in water
export inline constexpr auto FL_GRAPHED = (1 << 16); // worldgraph has this ent listed as something that blocks a connection

// UNDONE: Do we need these?
export inline constexpr auto FL_IMMUNE_WATER = (1 << 17);
export inline constexpr auto FL_IMMUNE_SLIME = (1 << 18);
export inline constexpr auto FL_IMMUNE_LAVA = (1 << 19);

export inline constexpr auto FL_PROXY = (1 << 20);	// This is a spectator proxy
export inline constexpr auto FL_ALWAYSTHINK = (1 << 21);	// Brush model flag -- call think every frame regardless of nextthink - ltime (for constantly changing velocity/path)
export inline constexpr auto FL_BASEVELOCITY = (1 << 22);	// Base velocity has been applied this frame (used to convert base velocity into momentum)
export inline constexpr auto FL_MONSTERCLIP = (1 << 23);	// Only collide in with monsters who have FL_MONSTERCLIP set
export inline constexpr auto FL_ONTRAIN = (1 << 24); // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
export inline constexpr auto FL_WORLDBRUSH = (1 << 25);	// Not moveable/removeable brush entity (really part of the world, but represented as an entity for transparency or something)
export inline constexpr auto FL_SPECTATOR = (1 << 26); // This client is a spectator, don't run touch functions, etc.
export inline constexpr auto FL_CUSTOMENTITY = (1 << 29);	// This is a custom entity
export inline constexpr auto FL_KILLME = (1 << 30);	// This entity is marked for death -- This allows the engine to kill ents at the appropriate time
export inline constexpr auto FL_DORMANT = (1 << 31);	// Entity is dormant, no updates to client


// Goes into globalvars_t.trace_flags
export inline constexpr auto FTRACE_SIMPLEBOX = (1 << 0);	// Traceline with a simple box


// walkmove modes
export inline constexpr auto WALKMOVE_NORMAL = 0;		// normal walkmove
export inline constexpr auto WALKMOVE_WORLDONLY = 1;	// doesn't hit ANY entities, no matter what the solid type
export inline constexpr auto WALKMOVE_CHECKONLY = 2;	// move, but don't touch triggers

// edict->movetype values
export inline constexpr auto MOVETYPE_NONE = 0;		// never moves
//export inline constexpr auto MOVETYPE_ANGLENOCLIP = 1;
//export inline constexpr auto MOVETYPE_ANGLECLIP = 2;
export inline constexpr auto MOVETYPE_WALK = 3;		// Player only - moving on the ground
export inline constexpr auto MOVETYPE_STEP = 4;		// gravity, special edge handling -- monsters use this
export inline constexpr auto MOVETYPE_FLY = 5;		// No gravity, but still collides with stuff
export inline constexpr auto MOVETYPE_TOSS = 6;		// gravity/collisions
export inline constexpr auto MOVETYPE_PUSH = 7;		// no clip to world, push and crush
export inline constexpr auto MOVETYPE_NOCLIP = 8;		// No gravity, no collisions, still do velocity/avelocity
export inline constexpr auto MOVETYPE_FLYMISSILE = 9;		// extra size to monsters
export inline constexpr auto MOVETYPE_BOUNCE = 10;		// Just like Toss, but reflect velocity when contacting surfaces
export inline constexpr auto MOVETYPE_BOUNCEMISSILE = 11;		// bounce w/o gravity
export inline constexpr auto MOVETYPE_FOLLOW = 12;		// track movement of aiment
export inline constexpr auto MOVETYPE_PUSHSTEP = 13;		// BSP model that needs physics/world collisions (uses nearest hull for world collision)

// edict->solid values
// NOTE: Some movetypes will cause collisions independent of SOLID_NOT/SOLID_TRIGGER when the entity moves
// SOLID only effects OTHER entities colliding with this one when they move - UGH!
export inline constexpr auto SOLID_NOT = 0;			// no interaction with other objects
export inline constexpr auto SOLID_TRIGGER = 1;		// touch on edge, but not blocking
export inline constexpr auto SOLID_BBOX = 2;		// touch on edge, block
export inline constexpr auto SOLID_SLIDEBOX = 3;	// touch on edge, but not an onground
export inline constexpr auto SOLID_BSP = 4;			// bsp clip, touch on edge, block

// edict->deadflag values
export inline constexpr auto DEAD_NO = 0; // alive
export inline constexpr auto DEAD_DYING = 1; // playing death animation or still falling off of a ledge waiting to hit ground
export inline constexpr auto DEAD_DEAD = 2; // dead. lying still.
export inline constexpr auto DEAD_RESPAWNABLE = 3;
export inline constexpr auto DEAD_DISCARDBODY = 4;

export inline constexpr auto DAMAGE_NO = 0;
export inline constexpr auto DAMAGE_YES = 1;
export inline constexpr auto DAMAGE_AIM = 2;

// entity effects
export inline constexpr auto EF_BRIGHTFIELD = 1;	// swirling cloud of particles
export inline constexpr auto EF_MUZZLEFLASH = 2;	// single frame ELIGHT on entity attachment 0
export inline constexpr auto EF_BRIGHTLIGHT = 4;	// DLIGHT centered at entity origin
export inline constexpr auto EF_DIMLIGHT = 8;	// player flashlight
export inline constexpr auto EF_INVLIGHT = 16;	// get lighting from ceiling
export inline constexpr auto EF_NOINTERP = 32;	// don't interpolate the next frame
export inline constexpr auto EF_LIGHT = 64;	// rocket flare glow sprite
export inline constexpr auto EF_NODRAW = 128;	// don't draw entity

// entity flags
export inline constexpr auto EFLAG_SLERP = 1;	// do studio interpolation of this entity

//
// temp entity events
//
export inline constexpr auto TE_BEAMPOINTS = 0;		// beam effect between two points
// coord coord coord (start position) 
// coord coord coord (end position) 
// short (sprite index) 
// byte (starting frame) 
// byte (frame rate in 0.1's) 
// byte (life in 0.1's) 
// byte (line width in 0.1's) 
// byte (noise amplitude in 0.01's) 
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

export inline constexpr auto TE_BEAMENTPOINT = 1;		// beam effect between point and entity
// short (start entity) 
// coord coord coord (end position) 
// short (sprite index) 
// byte (starting frame) 
// byte (frame rate in 0.1's) 
// byte (life in 0.1's) 
// byte (line width in 0.1's) 
// byte (noise amplitude in 0.01's) 
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

export inline constexpr auto TE_GUNSHOT = 2;		// particle effect plus ricochet sound
// coord coord coord (position) 

export inline constexpr auto TE_EXPLOSION = 3;		// additive sprite, 2 dynamic lights, flickering particles, explosion sound, move vertically 8 pps
// coord coord coord (position) 
// short (sprite index)
// byte (scale in 0.1's)
// byte (framerate)
// byte (flags)
//
// The Explosion effect has some flags to control performance/aesthetic features:
export inline constexpr auto TE_EXPLFLAG_NONE = 0;	// all flags clear makes default Half-Life explosion
export inline constexpr auto TE_EXPLFLAG_NOADDITIVE = 1;	// sprite will be drawn opaque (ensure that the sprite you send is a non-additive sprite)
export inline constexpr auto TE_EXPLFLAG_NODLIGHTS = 2;	// do not render dynamic lights
export inline constexpr auto TE_EXPLFLAG_NOSOUND = 4;	// do not play client explosion sound
export inline constexpr auto TE_EXPLFLAG_NOPARTICLES = 8;	// do not draw particles


export inline constexpr auto TE_TAREXPLOSION = 4;		// Quake1 "tarbaby" explosion with sound
// coord coord coord (position) 

export inline constexpr auto TE_SMOKE = 5;		// alphablend sprite, move vertically 30 pps
// coord coord coord (position) 
// short (sprite index)
// byte (scale in 0.1's)
// byte (framerate)

export inline constexpr auto TE_TRACER = 6;		// tracer effect from point to point
// coord, coord, coord (start) 
// coord, coord, coord (end)

export inline constexpr auto TE_LIGHTNING = 7;		// TE_BEAMPOINTS with simplified parameters
// coord, coord, coord (start) 
// coord, coord, coord (end) 
// byte (life in 0.1's) 
// byte (width in 0.1's) 
// byte (amplitude in 0.01's)
// short (sprite model index)

export inline constexpr auto TE_BEAMENTS = 8;
// short (start entity) 
// short (end entity) 
// short (sprite index) 
// byte (starting frame) 
// byte (frame rate in 0.1's) 
// byte (life in 0.1's) 
// byte (line width in 0.1's) 
// byte (noise amplitude in 0.01's) 
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

export inline constexpr auto TE_SPARKS = 9;		// 8 random tracers with gravity, ricochet sprite
// coord coord coord (position) 

export inline constexpr auto TE_LAVASPLASH = 10;		// Quake1 lava splash
// coord coord coord (position) 

export inline constexpr auto TE_TELEPORT = 11;		// Quake1 teleport splash
// coord coord coord (position) 

export inline constexpr auto TE_EXPLOSION2 = 12;		// Quake1 colormaped (base palette) particle explosion with sound
// coord coord coord (position) 
// byte (starting color)
// byte (num colors)

export inline constexpr auto TE_BSPDECAL = 13;		// Decal from the .BSP file 
// coord, coord, coord (x,y,z), decal position (center of texture in world)
// short (texture index of precached decal texture name)
// short (entity index)
// [optional - only included if previous short is non-zero (not the world)] short (index of model of above entity)

export inline constexpr auto TE_IMPLOSION = 14;		// tracers moving toward a point
// coord, coord, coord (position)
// byte (radius)
// byte (count)
// byte (life in 0.1's) 

export inline constexpr auto TE_SPRITETRAIL = 15;		// line of moving glow sprites with gravity, fadeout, and collisions
// coord, coord, coord (start) 
// coord, coord, coord (end) 
// short (sprite index)
// byte (count)
// byte (life in 0.1's) 
// byte (scale in 0.1's) 
// byte (velocity along vector in 10's)
// byte (randomness of velocity in 10's)

export inline constexpr auto TE_BEAM = 16;		// obsolete

export inline constexpr auto TE_SPRITE = 17;		// additive sprite, plays 1 cycle
// coord, coord, coord (position) 
// short (sprite index) 
// byte (scale in 0.1's) 
// byte (brightness)

export inline constexpr auto TE_BEAMSPRITE = 18;		// A beam with a sprite at the end
// coord, coord, coord (start position) 
// coord, coord, coord (end position) 
// short (beam sprite index) 
// short (end sprite index) 

export inline constexpr auto TE_BEAMTORUS = 19;		// screen aligned beam ring, expands to max radius over lifetime
// coord coord coord (center position) 
// coord coord coord (axis and radius) 
// short (sprite index) 
// byte (starting frame) 
// byte (frame rate in 0.1's) 
// byte (life in 0.1's) 
// byte (line width in 0.1's) 
// byte (noise amplitude in 0.01's) 
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

export inline constexpr auto TE_BEAMDISK = 20;		// disk that expands to max radius over lifetime
// coord coord coord (center position) 
// coord coord coord (axis and radius) 
// short (sprite index) 
// byte (starting frame) 
// byte (frame rate in 0.1's) 
// byte (life in 0.1's) 
// byte (line width in 0.1's) 
// byte (noise amplitude in 0.01's) 
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

export inline constexpr auto TE_BEAMCYLINDER = 21;		// cylinder that expands to max radius over lifetime
// coord coord coord (center position) 
// coord coord coord (axis and radius) 
// short (sprite index) 
// byte (starting frame) 
// byte (frame rate in 0.1's) 
// byte (life in 0.1's) 
// byte (line width in 0.1's) 
// byte (noise amplitude in 0.01's) 
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

export inline constexpr auto TE_BEAMFOLLOW = 22;		// create a line of decaying beam segments until entity stops moving
// short (entity:attachment to follow)
// short (sprite index)
// byte (life in 0.1's) 
// byte (line width in 0.1's) 
// byte,byte,byte (color)
// byte (brightness)

export inline constexpr auto TE_GLOWSPRITE = 23;
// coord, coord, coord (pos) short (model index) byte (scale / 10)

export inline constexpr auto TE_BEAMRING = 24;		// connect a beam ring to two entities
// short (start entity) 
// short (end entity) 
// short (sprite index) 
// byte (starting frame) 
// byte (frame rate in 0.1's) 
// byte (life in 0.1's) 
// byte (line width in 0.1's) 
// byte (noise amplitude in 0.01's) 
// byte,byte,byte (color)
// byte (brightness)
// byte (scroll speed in 0.1's)

export inline constexpr auto TE_STREAK_SPLASH = 25;		// oriented shower of tracers
// coord coord coord (start position) 
// coord coord coord (direction vector) 
// byte (color)
// short (count)
// short (base speed)
// short (ramdon velocity)

export inline constexpr auto TE_BEAMHOSE = 26;		// obsolete

export inline constexpr auto TE_DLIGHT = 27;		// dynamic light, effect world, minor entity effect
// coord, coord, coord (pos) 
// byte (radius in 10's) 
// byte byte byte (color)
// byte (brightness)
// byte (life in 10's)
// byte (decay rate in 10's)

export inline constexpr auto TE_ELIGHT = 28;		// point entity light, no world effect
// short (entity:attachment to follow)
// coord coord coord (initial position) 
// coord (radius)
// byte byte byte (color)
// byte (life in 0.1's)
// coord (decay rate)

export inline constexpr auto TE_TEXTMESSAGE = 29;
// short 1.2.13 x (-1 = center)
// short 1.2.13 y (-1 = center)
// byte Effect 0 = fade in/fade out
			// 1 is flickery credits
			// 2 is write out (training room)

// 4 bytes r,g,b,a color1	(text color)
// 4 bytes r,g,b,a color2	(effect color)
// ushort 8.8 fadein time
// ushort 8.8  fadeout time
// ushort 8.8 hold time
// optional ushort 8.8 fxtime	(time the highlight lags behing the leading text in effect 2)
// string text message		(512 chars max sz string)
export inline constexpr auto TE_LINE = 30;
// coord, coord, coord		startpos
// coord, coord, coord		endpos
// short life in 0.1 s
// 3 bytes r, g, b

export inline constexpr auto TE_BOX = 31;
// coord, coord, coord		boxmins
// coord, coord, coord		boxmaxs
// short life in 0.1 s
// 3 bytes r, g, b

export inline constexpr auto TE_KILLBEAM = 99;		// kill all beams attached to entity
// short (entity)

export inline constexpr auto TE_LARGEFUNNEL = 100;
// coord coord coord (funnel position)
// short (sprite index) 
// short (flags) 

export inline constexpr auto TE_BLOODSTREAM = 101;		// particle spray
// coord coord coord (start position)
// coord coord coord (spray vector)
// byte (color)
// byte (speed)

export inline constexpr auto TE_SHOWLINE = 102;		// line of particles every 5 units, dies in 30 seconds
// coord coord coord (start position)
// coord coord coord (end position)

export inline constexpr auto TE_BLOOD = 103;		// particle spray
// coord coord coord (start position)
// coord coord coord (spray vector)
// byte (color)
// byte (speed)

export inline constexpr auto TE_DECAL = 104;		// Decal applied to a brush entity (not the world)
// coord, coord, coord (x,y,z), decal position (center of texture in world)
// byte (texture index of precached decal texture name)
// short (entity index)

export inline constexpr auto TE_FIZZ = 105;		// create alpha sprites inside of entity, float upwards
// short (entity)
// short (sprite index)
// byte (density)

export inline constexpr auto TE_MODEL = 106;		// create a moving model that bounces and makes a sound when it hits
// coord, coord, coord (position) 
// coord, coord, coord (velocity)
// angle (initial yaw)
// short (model index)
// byte (bounce sound type)
// byte (life in 0.1's)

export inline constexpr auto TE_EXPLODEMODEL = 107;		// spherical shower of models, picks from set
// coord, coord, coord (origin)
// coord (velocity)
// short (model index)
// short (count)
// byte (life in 0.1's)

export inline constexpr auto TE_BREAKMODEL = 108;		// box of models or sprites
// coord, coord, coord (position)
// coord, coord, coord (size)
// coord, coord, coord (velocity)
// byte (random velocity in 10's)
// short (sprite or model index)
// byte (count)
// byte (life in 0.1 secs)
// byte (flags)

export inline constexpr auto TE_GUNSHOTDECAL = 109;		// decal and ricochet sound
// coord, coord, coord (position)
// short (entity index???)
// byte (decal???)

export inline constexpr auto TE_SPRITE_SPRAY = 110;		// spay of alpha sprites
// coord, coord, coord (position)
// coord, coord, coord (velocity)
// short (sprite index)
// byte (count)
// byte (speed)
// byte (noise)

export inline constexpr auto TE_ARMOR_RICOCHET = 111;		// quick spark sprite, client ricochet sound. 
// coord, coord, coord (position)
// byte (scale in 0.1's)

export inline constexpr auto TE_PLAYERDECAL = 112;		// ???
// byte (playerindex)
// coord, coord, coord (position)
// short (entity???)
// byte (decal number???)
// [optional] short (model index???)

export inline constexpr auto TE_BUBBLES = 113;		// create alpha sprites inside of box, float upwards
// coord, coord, coord (min start position)
// coord, coord, coord (max start position)
// coord (float height)
// short (model index)
// byte (count)
// coord (speed)

export inline constexpr auto TE_BUBBLETRAIL = 114;		// create alpha sprites along a line, float upwards
// coord, coord, coord (min start position)
// coord, coord, coord (max start position)
// coord (float height)
// short (model index)
// byte (count)
// coord (speed)

export inline constexpr auto TE_BLOODSPRITE = 115;		// spray of opaque sprite1's that fall, single sprite2 for 1..2 secs (this is a high-priority tent)
// coord, coord, coord (position)
// short (sprite1 index)
// short (sprite2 index)
// byte (color)
// byte (scale)

export inline constexpr auto TE_WORLDDECAL = 116;		// Decal applied to the world brush
// coord, coord, coord (x,y,z), decal position (center of texture in world)
// byte (texture index of precached decal texture name)

export inline constexpr auto TE_WORLDDECALHIGH = 117;		// Decal (with texture index > 256) applied to world brush
// coord, coord, coord (x,y,z), decal position (center of texture in world)
// byte (texture index of precached decal texture name - 256)

export inline constexpr auto TE_DECALHIGH = 118;		// Same as TE_DECAL, but the texture index was greater than 256
// coord, coord, coord (x,y,z), decal position (center of texture in world)
// byte (texture index of precached decal texture name - 256)
// short (entity index)

export inline constexpr auto TE_PROJECTILE = 119;		// Makes a projectile (like a nail) (this is a high-priority tent)
// coord, coord, coord (position)
// coord, coord, coord (velocity)
// short (modelindex)
// byte (life)
// byte (owner)  projectile won't collide with owner (if owner == 0, projectile will hit any client).

export inline constexpr auto TE_SPRAY = 120;		// Throws a shower of sprites or models
// coord, coord, coord (position)
// coord, coord, coord (direction)
// short (modelindex)
// byte (count)
// byte (speed)
// byte (noise)
// byte (rendermode)

export inline constexpr auto TE_PLAYERSPRITES = 121;		// sprites emit from a player's bounding box (ONLY use for players!)
// byte (playernum)
// short (sprite modelindex)
// byte (count)
// byte (variance) (0 = no variance in size) (10 = 10% variance in size)

export inline constexpr auto TE_PARTICLEBURST = 122;		// very similar to lavasplash.
// coord (origin)
// short (radius)
// byte (particle color)
// byte (duration * 10) (will be randomized a bit)

export inline constexpr auto TE_FIREFIELD = 123;		// makes a field of fire.
// coord (origin)
// short (radius) (fire is made in a square around origin. -radius, -radius to radius, radius)
// short (modelindex)
// byte (count)
// byte (flags)
// byte (duration (in seconds) * 10) (will be randomized a bit)
//
// to keep network traffic low, this message has associated flags that fit into a byte:
export inline constexpr auto TEFIRE_FLAG_ALLFLOAT = 1; // all sprites will drift upwards as they animate
export inline constexpr auto TEFIRE_FLAG_SOMEFLOAT = 2; // some of the sprites will drift upwards. (50% chance)
export inline constexpr auto TEFIRE_FLAG_LOOP = 4; // if set, sprite plays at 15 fps, otherwise plays at whatever rate stretches the animation over the sprite's duration.
export inline constexpr auto TEFIRE_FLAG_ALPHA = 8; // if set, sprite is rendered alpha blended at 50% else, opaque
export inline constexpr auto TEFIRE_FLAG_PLANAR = 16; // if set, all fire sprites have same initial Z instead of randomly filling a cube. 

export inline constexpr auto TE_PLAYERATTACHMENT = 124; // attaches a TENT to a player (this is a high-priority tent)
// byte (entity index of player)
// coord (vertical offset) ( attachment origin.z = player origin.z + vertical offset )
// short (model index)
// short (life * 10 );

export inline constexpr auto TE_KILLPLAYERATTACHMENTS = 125; // will expire all TENTS attached to a player.
// byte (entity index of player)

export inline constexpr auto TE_MULTIGUNSHOT = 126; // much more compact shotgun message
// This message is used to make a client approximate a 'spray' of gunfire.
// Any weapon that fires more than one bullet per frame and fires in a bit of a spread is
// a good candidate for MULTIGUNSHOT use. (shotguns)
//
// NOTE: This effect makes the client do traces for each bullet, these client traces ignore
//		 entities that have studio models.Traces are 4096 long.
//
// coord (origin)
// coord (origin)
// coord (origin)
// coord (direction)
// coord (direction)
// coord (direction)
// coord (x noise * 100)
// coord (y noise * 100)
// byte (count)
// byte (bullethole decal texture index)

export inline constexpr auto TE_USERTRACER = 127; // larger message than the standard tracer, but allows some customization.
// coord (origin)
// coord (origin)
// coord (origin)
// coord (velocity)
// coord (velocity)
// coord (velocity)
// byte ( life * 10 )
// byte ( color ) this is an index into an array of color vectors in the engine. (0 - )
// byte ( length * 10 )



export inline constexpr auto MSG_BROADCAST = 0;			// unreliable to all
export inline constexpr auto MSG_ONE = 1;				// reliable to one (msg_entity)
export inline constexpr auto MSG_ALL = 2;				// reliable to all
export inline constexpr auto MSG_INIT = 3;				// write to the init string
export inline constexpr auto MSG_PVS = 4;				// Ents in PVS of org
export inline constexpr auto MSG_PAS = 5;				// Ents in PAS of org
export inline constexpr auto MSG_PVS_R = 6;				// Reliable to PVS
export inline constexpr auto MSG_PAS_R = 7;				// Reliable to PAS
export inline constexpr auto MSG_ONE_UNRELIABLE = 8;	// Send to one client, but don't put in reliable stream, put in unreliable datagram ( could be dropped )
export inline constexpr auto MSG_SPEC = 9;				// Sends to all spectator proxies

// contents of a spot in the world
export inline constexpr auto CONTENTS_EMPTY = -1;
export inline constexpr auto CONTENTS_SOLID = -2;
export inline constexpr auto CONTENTS_WATER = -3;
export inline constexpr auto CONTENTS_SLIME = -4;
export inline constexpr auto CONTENTS_LAVA = -5;
export inline constexpr auto CONTENTS_SKY = -6;
/* These additional contents constants are defined in bspfile.h
export inline constexpr auto CONTENTS_ORIGIN		-7		// removed at csg time
export inline constexpr auto CONTENTS_CLIP		-8		// changed to contents_solid
export inline constexpr auto CONTENTS_CURRENT_0		-9
export inline constexpr auto CONTENTS_CURRENT_90		-10
export inline constexpr auto CONTENTS_CURRENT_180	-11
export inline constexpr auto CONTENTS_CURRENT_270	-12
export inline constexpr auto CONTENTS_CURRENT_UP		-13
export inline constexpr auto CONTENTS_CURRENT_DOWN	-14

export inline constexpr auto CONTENTS_TRANSLUCENT	-15
*/
export inline constexpr auto CONTENTS_LADDER = -16;

export inline constexpr auto CONTENT_EMPTY = -1;
export inline constexpr auto CONTENT_SOLID = -2;
export inline constexpr auto CONTENT_WATER = -3;
export inline constexpr auto CONTENT_SLIME = -4;
export inline constexpr auto CONTENT_LAVA = -5;
export inline constexpr auto CONTENT_SKY = -6;

// channels
export inline constexpr auto CHAN_AUTO = 0;
export inline constexpr auto CHAN_WEAPON = 1;
export inline constexpr auto CHAN_VOICE = 2;
export inline constexpr auto CHAN_ITEM = 3;
export inline constexpr auto CHAN_BODY = 4;
export inline constexpr auto CHAN_STREAM = 5;			// allocate stream channel from the static or dynamic area
export inline constexpr auto CHAN_STATIC = 6;			// allocate channel from the static area 
export inline constexpr auto CHAN_NETWORKVOICE_BASE = 7;		// voice data coming across the network
export inline constexpr auto CHAN_NETWORKVOICE_END = 500;		// network voice data reserves slots (CHAN_NETWORKVOICE_BASE through CHAN_NETWORKVOICE_END).

// attenuation values
export inline constexpr auto ATTN_NONE = 0;
export inline constexpr auto ATTN_NORM = (float)0.8;
export inline constexpr auto ATTN_IDLE = (float)2;
export inline constexpr auto ATTN_STATIC = (float)1.25;

// pitch values
export inline constexpr auto PITCH_NORM = 100;			// non-pitch shifted
export inline constexpr auto PITCH_LOW = 95;			// other values are possible - 0-255, where 255 is very high
export inline constexpr auto PITCH_HIGH = 120;

// volume values
export inline constexpr auto VOL_NORM = 1.0;

// plats
export inline constexpr auto PLAT_LOW_TRIGGER = 1;

// Trains
export inline constexpr auto SF_TRAIN_WAIT_RETRIGGER = 1;
export inline constexpr auto SF_TRAIN_PASSABLE = 8;		// Train is not solid -- used to make water trains

// buttons
export import in_buttons;

// Break Model Defines

export inline constexpr auto BREAK_TYPEMASK = 0x4F;
export inline constexpr auto BREAK_GLASS = 0x01;
export inline constexpr auto BREAK_METAL = 0x02;
export inline constexpr auto BREAK_FLESH = 0x04;
export inline constexpr auto BREAK_WOOD = 0x08;

export inline constexpr auto BREAK_SMOKE = 0x10;
export inline constexpr auto BREAK_TRANS = 0x20;
export inline constexpr auto BREAK_CONCRETE = 0x40;
export inline constexpr auto BREAK_2 = 0x80;

// Colliding temp entity sounds

export inline constexpr auto BOUNCE_GLASS = BREAK_GLASS;
export inline constexpr auto BOUNCE_METAL = BREAK_METAL;
export inline constexpr auto BOUNCE_FLESH = BREAK_FLESH;
export inline constexpr auto BOUNCE_WOOD = BREAK_WOOD;
export inline constexpr auto BOUNCE_SHRAP = 0x10;
export inline constexpr auto BOUNCE_SHELL = 0x20;
export inline constexpr auto BOUNCE_CONCRETE = BREAK_CONCRETE;
export inline constexpr auto BOUNCE_SHOTSHELL = 0x80;

// Temp entity bounce sound types
export inline constexpr auto TE_BOUNCE_NULL = 0;
export inline constexpr auto TE_BOUNCE_SHELL = 1;
export inline constexpr auto TE_BOUNCE_SHOTSHELL = 2;

// Rendering constants
export enum kRenderFn
{
	kRenderNormal,			// src
	kRenderTransColor,		// c*a+dest*(1-a)
	kRenderTransTexture,	// src*a+dest*(1-a)
	kRenderGlow,			// src*a+dest -- No Z buffer checks
	kRenderTransAlpha,		// src*srca+dest*(1-srca)
	kRenderTransAdd,		// src*a+dest
};

export enum  kRenderFx
{
	kRenderFxNone = 0,
	kRenderFxPulseSlow,
	kRenderFxPulseFast,
	kRenderFxPulseSlowWide,
	kRenderFxPulseFastWide,
	kRenderFxFadeSlow,
	kRenderFxFadeFast,
	kRenderFxSolidSlow,
	kRenderFxSolidFast,
	kRenderFxStrobeSlow,
	kRenderFxStrobeFast,
	kRenderFxStrobeFaster,
	kRenderFxFlickerSlow,
	kRenderFxFlickerFast,
	kRenderFxNoDissipation,
	kRenderFxDistort,			// Distort/scale/translate flicker
	kRenderFxHologram,			// kRenderFxDistort + distance fade
	kRenderFxDeadPlayer,		// kRenderAmt is the player index
	kRenderFxExplode,			// Scale up really big!
	kRenderFxGlowShell,			// Glowing Shell
	kRenderFxClampMinScale,		// Keep this sprite from getting very small (SPRITES only!)
};


export using func_t = int;
export using string_t = int;

export using byte = std::uint8_t;
export using word = std::uint16_t;

export using qboolean = int;

export struct color24
{
	byte r, g, b;
};

export struct colorVec
{
	unsigned r, g, b, a;
};

export struct PackedColorVec
{
	unsigned short r, g, b, a;
};

export struct plane_t
{
	vec3_t	normal;
	float	dist;
};

export struct trace_t
{
	qboolean	allsolid;	// if true, plane is not valid
	qboolean	startsolid;	// if true, the initial point was in a solid area
	qboolean	inopen, inwater;
	float		fraction;		// time completed, 1.0 = didn't hit anything
	vec3_t		endpos;			// final position
	plane_t		plane;			// surface normal at impact
	edict_t		*ent;			// entity the surface is on
	int			hitgroup;		// 0 == generic, non zero is specific body part
};