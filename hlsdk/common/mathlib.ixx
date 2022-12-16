export module mathlib;

export import vector;

//typedef float vec_t;
//typedef vec_t vec3_t[3];
export using vec4_t = vec_t[4];	// x,y,z,w
export using vec5_t = vec_t[5];

export using vec_s_t = short;
export using vec3s_t = vec_s_t[3];
export using vec4s_t = vec_s_t[4];	// x,y,z,w
export using vec5s_t = vec_s_t[5];

export using fixed4_t = int;
export using fixed8_t = int;
export using fixed16_t = int;

//#ifndef M_PI
//#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
//#endif
//
//struct mplane_s;
//
//extern vec3_t vec3_origin;
//extern	int nanmask;

export inline constexpr bool IS_NAN(std::floating_point auto fl) noexcept { return fl != fl; }

export inline constexpr void VectorSubtract(auto const &&a, auto const &&b, auto &c) noexcept { c[0] = a[0] - b[0]; c[1] = a[1] - b[1]; c[2] = a[2] - b[2]; }
export inline constexpr void VectorAdd(auto const &&a, auto const &&b, auto &c) noexcept { c[0] = a[0] + b[0]; c[1] = a[1] + b[1]; c[2] = a[2] + b[2]; }
export inline constexpr void VectorCopy(auto const &&a, auto &b) noexcept { b[0] = a[0]; b[1] = a[1]; b[2] = a[2]; }
export inline constexpr void VectorClear(auto &a) noexcept { a[0] = 0; a[1] = 0; a[2] = 0; }

export void VectorMA(const vec3_t veca, float scale, const vec3_t vecb, vec3_t vecc);

export vec_t _DotProduct(vec3_t v1, vec3_t v2);
export void _VectorSubtract(vec3_t veca, vec3_t vecb, vec3_t out);
export void _VectorAdd(vec3_t veca, vec3_t vecb, vec3_t out);
export void _VectorCopy(vec3_t in, vec3_t out);

export int VectorCompare(const vec3_t v1, const vec3_t v2);
export float Length(const vec3_t v);
export void CrossProduct(const vec3_t v1, const vec3_t v2, vec3_t cross);
export float VectorNormalize(vec3_t v);		// returns vector length
export void VectorInverse(vec3_t v);
export void VectorScale(const vec3_t in, vec_t scale, vec3_t out);
export int Q_log2(int val);

export void R_ConcatRotations(float in1[3][3], float in2[3][3], float out[3][3]);
export void R_ConcatTransforms(float in1[3][4], float in2[3][4], float out[3][4]);

// Here are some "manual" INLINE routines for doing floating point to integer conversions
inline short new_cw, old_cw;

export union DLONG
{
	int		i[2];
	double	d;
	float	f;
};

inline DLONG	dlong;

#ifdef _WIN32
export void __inline set_fpu_cw(void) noexcept
{
	_asm
	{		wait
		fnstcw	old_cw
		wait
		mov		ax, word ptr old_cw
		or ah, 0xc
		mov		word ptr new_cw, ax
		fldcw	new_cw
	}
}

export int __inline quick_ftol(float f) noexcept
{
	_asm {
		// Assumes that we are already in chop mode, and only need a 32-bit int
		fld		DWORD PTR f
		fistp	DWORD PTR dlong
	}
	return dlong.i[0];
}

export void __inline restore_fpu_cw(void) noexcept
{
	_asm	fldcw	old_cw
}
#else
#define set_fpu_cw() /* */
#define quick_ftol(f) ftol(f)
#define restore_fpu_cw() /* */
#endif

export void FloorDivMod(double numer, double denom, int *quotient, int *rem);
export fixed16_t Invert24To16(fixed16_t val);
export int GreatestCommonDivisor(int i1, int i2);

export void AngleVectors(const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
export void AngleVectorsTranspose(const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
//export inline constexpr auto AngleIVectors = AngleVectorsTranspose; #UNDONE

export void AngleMatrix(const vec3_t angles, float(*matrix)[4]);
export void AngleIMatrix(const vec3_t angles, float(*matrix)[4]);
export void VectorTransform(const vec3_t in1, float in2[3][4], vec3_t out);

export void NormalizeAngles(vec3_t angles);
export void InterpolateAngles(vec3_t start, vec3_t end, vec3_t output, float frac);
export float AngleBetweenVectors(const vec3_t v1, const vec3_t v2);


export void VectorMatrix(vec3_t forward, vec3_t right, vec3_t up);
export void VectorAngles(const vec3_t forward, vec3_t angles);

export int InvertMatrix(const float *m, float *out);

export int BoxOnPlaneSide(vec3_t emins, vec3_t emaxs, struct mplane_s *plane);
export float anglemod(float a);

export inline auto BOX_ON_PLANE_SIDE(auto const &&emins, auto const &&emaxs, auto const &&p) noexcept
{
	return (((p)->type < 3) ?
		(
			((p)->dist <= (emins)[(p)->type]) ?
			1
			:
			(
				((p)->dist >= (emaxs)[(p)->type]) ?
				2
				:
				3
				)
			)
		:
		BoxOnPlaneSide((emins), (emaxs), (p)));
}
