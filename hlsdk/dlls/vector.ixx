module;

#include <cmath>

export module vector;

export using vec_t = float;

//=========================================================
// 2DVector - used for many pathfinding and many other 
// operations that are treated as planar rather than 3d.
//=========================================================
export struct Vector2D
{
	inline Vector2D(void) noexcept : x(0.0), y(0.0) { }
	inline Vector2D(float X, float Y) noexcept : x(0.0), y(0.0) { x = X; y = Y; }
	inline Vector2D operator+(const Vector2D &v) const noexcept { return Vector2D(x + v.x, y + v.y); }
	inline Vector2D operator-(const Vector2D &v) const noexcept { return Vector2D(x - v.x, y - v.y); }
	inline Vector2D operator*(float fl) const noexcept { return Vector2D(x * fl, y * fl); }
	inline Vector2D operator/(float fl) const noexcept { fl = 1 / fl; return Vector2D(x * fl, y * fl); }

	inline float Length(void) const noexcept { return (float)sqrt(x * x + y * y); }

	inline Vector2D Normalize(void) const noexcept
	{
		// Vector2D vec2;

		float flLen = Length();
		if (flLen == 0)
		{
			return Vector2D(0, 0);
		}
		else
		{
			flLen = 1 / flLen;
			return Vector2D(x * flLen, y * flLen);
		}
	}

	vec_t   x, y;
};

export float DotProduct(const Vector2D &a, const Vector2D &b) noexcept { return a.x * b.x + a.y * b.y; }
export Vector2D operator*(float fl, const Vector2D &v) noexcept { return v * fl; }

//=========================================================
// 3D Vector
//=========================================================
export struct Vector                                            // same data-layout as engine's vec3_t,
{                                                               //              which is a vec_t[3]
	// Construction/destruction
	inline Vector(void) noexcept : x(0.0), y(0.0), z(0.0) { }
	inline Vector(float X, float Y, float Z) noexcept : x(0.0), y(0.0), z(0.0) { x = X; y = Y; z = Z; }
	//inline Vector(double X, double Y, double Z)                   { x = (float)X; y = (float)Y; z = (float)Z;     }
	//inline Vector(int X, int Y, int Z)                            { x = (float)X; y = (float)Y; z = (float)Z;     }
	inline Vector(const Vector &v) noexcept : x(0.0), y(0.0), z(0.0) { x = v.x; y = v.y; z = v.z; }
	inline Vector(float rgfl[3]) noexcept : x(0.0), y(0.0), z(0.0) { x = rgfl[0]; y = rgfl[1]; z = rgfl[2]; }
	inline Vector(const Vector2D &v) noexcept : x(0.0), y(0.0), z(0.0) { x = v.x; y = v.y; }

	// Operators
	inline Vector operator-(void) const noexcept { return Vector(-x, -y, -z); }
	inline int operator==(const Vector &v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	//inline int operator!=(const Vector &v) const { return !(*this == v); } // LUNA: CPP20 - auto generated.
	inline Vector operator+(const Vector &v) const noexcept { return Vector(x + v.x, y + v.y, z + v.z); }
	inline Vector operator-(const Vector &v) const noexcept { return Vector(x - v.x, y - v.y, z - v.z); }
	inline Vector operator*(float fl) const noexcept { return Vector(x * fl, y * fl, z * fl); }
	inline Vector operator/(float fl) const noexcept { fl = 1 / fl; return Vector(x * fl, y * fl, z * fl); }

	// Methods
	inline void CopyToArray(float *rgfl) const noexcept { rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; }
	inline float Length(void) const noexcept { return (float)sqrt(x * x + y * y + z * z); }
	inline operator float *() noexcept { return &x; } // Vectors will now automatically convert to float * when needed
	inline operator Vector2D () const noexcept { return (*this).Make2D(); }

#if !defined(__GNUC__) || (__GNUC__ >= 3)
	inline operator const float *() const noexcept { return &x; } // Vectors will now automatically convert to float * when needed
#endif

	inline Vector Normalize(void) const noexcept
	{
		float flLen = Length();
		if (flLen == 0) return Vector(0, 0, 1); // ????
		flLen = 1 / flLen;
		return Vector(x * flLen, y * flLen, z * flLen);
	}

	inline Vector2D Make2D(void) const noexcept
	{
		Vector2D        Vec2;

		Vec2.x = x;
		Vec2.y = y;

		return Vec2;
	}
	inline float Length2D(void) const noexcept { return (float)sqrt(x * x + y * y); }

	// Members
	vec_t x, y, z;
};

export Vector operator*(float fl, const Vector &v) noexcept { return v * fl; }
export float DotProduct(const Vector &a, const Vector &b) noexcept { return(a.x * b.x + a.y * b.y + a.z * b.z); }
export Vector CrossProduct(const Vector &a, const Vector &b) noexcept { return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

// LUNA: watchout for the freaking marcos.
export using vec3_t = Vector;
