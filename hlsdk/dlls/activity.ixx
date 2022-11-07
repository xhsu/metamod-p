export module activity;

export enum Activity
{
	ACT_RESET,
	ACT_IDLE,
	ACT_GUARD,
	ACT_WALK,
	ACT_RUN,
	ACT_FLY,
	ACT_SWIM,
	ACT_HOP,
	ACT_LEAP,
	ACT_FALL,
	ACT_LAND,
	ACT_STRAFE_LEFT,
	ACT_STRAFE_RIGHT,
	ACT_ROLL_LEFT,
	ACT_ROLL_RIGHT,
	ACT_TURN_LEFT,
	ACT_TURN_RIGHT,
	ACT_CROUCH,
	ACT_CROUCHIDLE,
	ACT_STAND,
	ACT_USE,
	ACT_SIGNAL1,
	ACT_SIGNAL2,
	ACT_SIGNAL3,
	ACT_TWITCH,
	ACT_COWER,
	ACT_SMALL_FLINCH,
	ACT_BIG_FLINCH,
	ACT_RANGE_ATTACK1,
	ACT_RANGE_ATTACK2,
	ACT_MELEE_ATTACK1,
	ACT_MELEE_ATTACK2,
	ACT_RELOAD,
	ACT_ARM,
	ACT_DISARM,
	ACT_EAT,
	ACT_DIESIMPLE,
	ACT_DIEBACKWARD,
	ACT_DIEFORWARD,
	ACT_DIEVIOLENT,
	ACT_BARNACLE_HIT,
	ACT_BARNACLE_PULL,
	ACT_BARNACLE_CHOMP,
	ACT_BARNACLE_CHEW,
	ACT_SLEEP,
	ACT_INSPECT_FLOOR,
	ACT_INSPECT_WALL,
	ACT_IDLE_ANGRY,
	ACT_WALK_HURT,
	ACT_RUN_HURT,
	ACT_HOVER,
	ACT_GLIDE,
	ACT_FLY_LEFT,
	ACT_FLY_RIGHT,
	ACT_DETECT_SCENT,
	ACT_SNIFF,
	ACT_BITE,
	ACT_THREAT_DISPLAY,
	ACT_FEAR_DISPLAY,
	ACT_EXCITED,
	ACT_SPECIAL_ATTACK1,
	ACT_SPECIAL_ATTACK2,
	ACT_COMBAT_IDLE,
	ACT_WALK_SCARED,
	ACT_RUN_SCARED,
	ACT_VICTORY_DANCE,
	ACT_DIE_HEADSHOT,
	ACT_DIE_CHESTSHOT,
	ACT_DIE_GUTSHOT,
	ACT_DIE_BACKSHOT,
	ACT_FLINCH_HEAD,
	ACT_FLINCH_CHEST,
	ACT_FLINCH_STOMACH,
	ACT_FLINCH_LEFTARM,
	ACT_FLINCH_RIGHTARM,
	ACT_FLINCH_LEFTLEG,
	ACT_FLINCH_RIGHTLEG,
	ACT_FLINCH,
	ACT_LARGE_FLINCH,
	ACT_HOLDBOMB,
	ACT_IDLE_FIDGET,
	ACT_IDLE_SCARED,
	ACT_IDLE_SCARED_FIDGET,
	ACT_FOLLOW_IDLE,
	ACT_FOLLOW_IDLE_FIDGET,
	ACT_FOLLOW_IDLE_SCARED,
	ACT_FOLLOW_IDLE_SCARED_FIDGET,
	ACT_CROUCH_IDLE,
	ACT_CROUCH_IDLE_FIDGET,
	ACT_CROUCH_IDLE_SCARED,
	ACT_CROUCH_IDLE_SCARED_FIDGET,
	ACT_CROUCH_WALK,
	ACT_CROUCH_WALK_SCARED,
	ACT_CROUCH_DIE,
	ACT_WALK_BACK,
	ACT_IDLE_SNEAKY,
	ACT_IDLE_SNEAKY_FIDGET,
	ACT_WALK_SNEAKY,
	ACT_WAVE,
	ACT_YES,
	ACT_NO
};

export struct activity_map_t
{
	int type;
	const char *name;
};

#define _A(a) { a, #a }

export inline constexpr activity_map_t activity_map[] =
{
	_A(ACT_IDLE),
	_A(ACT_GUARD),
	_A(ACT_WALK),
	_A(ACT_RUN),
	_A(ACT_FLY),
	_A(ACT_SWIM),
	_A(ACT_HOP),
	_A(ACT_LEAP),
	_A(ACT_FALL),
	_A(ACT_LAND),
	_A(ACT_STRAFE_LEFT),
	_A(ACT_STRAFE_RIGHT),
	_A(ACT_ROLL_LEFT),
	_A(ACT_ROLL_RIGHT),
	_A(ACT_TURN_LEFT),
	_A(ACT_TURN_RIGHT),
	_A(ACT_CROUCH),
	_A(ACT_CROUCHIDLE),
	_A(ACT_STAND),
	_A(ACT_USE),
	_A(ACT_SIGNAL1),
	_A(ACT_SIGNAL2),
	_A(ACT_SIGNAL3),
	_A(ACT_TWITCH),
	_A(ACT_COWER),
	_A(ACT_SMALL_FLINCH),
	_A(ACT_BIG_FLINCH),
	_A(ACT_RANGE_ATTACK1),
	_A(ACT_RANGE_ATTACK2),
	_A(ACT_MELEE_ATTACK1),
	_A(ACT_MELEE_ATTACK2),
	_A(ACT_RELOAD),
	_A(ACT_ARM),
	_A(ACT_DISARM),
	_A(ACT_EAT),
	_A(ACT_DIESIMPLE),
	_A(ACT_DIEBACKWARD),
	_A(ACT_DIEFORWARD),
	_A(ACT_DIEVIOLENT),
	_A(ACT_BARNACLE_HIT),
	_A(ACT_BARNACLE_PULL),
	_A(ACT_BARNACLE_CHOMP),
	_A(ACT_BARNACLE_CHEW),
	_A(ACT_SLEEP),
	_A(ACT_INSPECT_FLOOR),
	_A(ACT_INSPECT_WALL),
	_A(ACT_IDLE_ANGRY),
	_A(ACT_WALK_HURT),
	_A(ACT_RUN_HURT),
	_A(ACT_HOVER),
	_A(ACT_GLIDE),
	_A(ACT_FLY_LEFT),
	_A(ACT_FLY_RIGHT),
	_A(ACT_DETECT_SCENT),
	_A(ACT_SNIFF),
	_A(ACT_BITE),
	_A(ACT_THREAT_DISPLAY),
	_A(ACT_FEAR_DISPLAY),
	_A(ACT_EXCITED),
	_A(ACT_SPECIAL_ATTACK1),
	_A(ACT_SPECIAL_ATTACK2),
	_A(ACT_COMBAT_IDLE),
	_A(ACT_WALK_SCARED),
	_A(ACT_RUN_SCARED),
	_A(ACT_VICTORY_DANCE),
	_A(ACT_DIE_HEADSHOT),
	_A(ACT_DIE_CHESTSHOT),
	_A(ACT_DIE_GUTSHOT),
	_A(ACT_DIE_BACKSHOT),
	_A(ACT_FLINCH_HEAD),
	_A(ACT_FLINCH_CHEST),
	_A(ACT_FLINCH_STOMACH),
	_A(ACT_FLINCH_LEFTARM),
	_A(ACT_FLINCH_RIGHTARM),
	_A(ACT_FLINCH_LEFTLEG),
	_A(ACT_FLINCH_RIGHTLEG),
	_A(ACT_FLINCH),
	_A(ACT_LARGE_FLINCH),
	_A(ACT_HOLDBOMB),
	_A(ACT_IDLE_FIDGET),
	_A(ACT_IDLE_SCARED),
	_A(ACT_IDLE_SCARED_FIDGET),
	_A(ACT_FOLLOW_IDLE),
	_A(ACT_FOLLOW_IDLE_FIDGET),
	_A(ACT_FOLLOW_IDLE_SCARED),
	_A(ACT_FOLLOW_IDLE_SCARED_FIDGET),
	_A(ACT_CROUCH_IDLE),
	_A(ACT_CROUCH_IDLE_FIDGET),
	_A(ACT_CROUCH_IDLE_SCARED),
	_A(ACT_CROUCH_IDLE_SCARED_FIDGET),
	_A(ACT_CROUCH_WALK),
	_A(ACT_CROUCH_WALK_SCARED),
	_A(ACT_CROUCH_DIE),
	_A(ACT_WALK_BACK),
	_A(ACT_IDLE_SNEAKY),
	_A(ACT_IDLE_SNEAKY_FIDGET),
	_A(ACT_WALK_SNEAKY),
	_A(ACT_WAVE),
	_A(ACT_YES),
	_A(ACT_NO),
	{ 0, nullptr }
};
