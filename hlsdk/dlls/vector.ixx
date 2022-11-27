export module vector;

import <cmath>;
import <limits>;
import <numbers>;

export using vec_t = float;

//=========================================================
// 2DVector - used for many pathfinding and many other 
// operations that are treated as planar rather than 3d.
//=========================================================
export struct Vector2D
{
	constexpr inline Vector2D(void) noexcept = default;
	constexpr inline Vector2D(double X, double Y) noexcept : x{ (float)X }, y{ (float)Y } {}
	constexpr inline Vector2D(const Vector2D &rhs) noexcept = default;

	// Special status
	static inline consteval Vector2D Zero(void) noexcept { return Vector2D(0, 0); }
	static inline consteval Vector2D Right(void) noexcept { return Vector2D(0, -1); }
	static inline consteval Vector2D Left(void) noexcept { return Vector2D(0, 1); }
	static inline consteval Vector2D Forward(void) noexcept { return Vector2D(1, 0); }
	static inline consteval Vector2D Rearward(void) noexcept { return Vector2D(-1, 0); }

	inline Vector2D operator+(const Vector2D &v) const noexcept { return Vector2D(x + v.x, y + v.y); }
	inline Vector2D operator-(const Vector2D &v) const noexcept { return Vector2D(x - v.x, y - v.y); }
	inline Vector2D operator*(float fl) const noexcept { return Vector2D(x * fl, y * fl); }
	inline Vector2D operator/(float fl) const noexcept { fl = 1 / fl; return Vector2D(x * fl, y * fl); }

	inline double LengthSquared(void) const noexcept { return x * x + y * y; }
	inline double Length(void) const noexcept { return sqrt(LengthSquared()); }

	inline Vector2D Normalize(void) const noexcept
	{
		auto const flLength = Length();

		if (flLength <= std::numeric_limits<vec_t>::epsilon())
			return Vector2D();

		return Vector2D(x / flLength, y / flLength);
	}

	vec_t x{}, y{};
};

export float DotProduct(const Vector2D &a, const Vector2D &b) noexcept { return a.x * b.x + a.y * b.y; }
export Vector2D operator*(float fl, const Vector2D &v) noexcept { return v * fl; }

//=========================================================
// 3D Vector
//=========================================================
export struct Vector                                            // same data-layout as engine's vec3_t,
{                                                               //              which is a vec_t[3]
	// Construction/destruction
	constexpr inline Vector(void) noexcept = default;
	constexpr inline Vector(double X, double Y, double Z) noexcept : x{ (float)X }, y{ (float)Y }, z{ (float)Z } {}
	constexpr inline Vector(Vector2D const &v2, double Z) noexcept : x{ v2.x }, y{ v2.y }, z{ (float)Z } {}
	constexpr inline Vector(const Vector &rhs) noexcept = default;

	// Special status
	static inline constexpr Vector Zero(void) noexcept { return Vector(0, 0, 0); }	// #UPDATE_AT_CPP23 P2564R0 "consteval needs to propagate up"
	static inline constexpr Vector Up(void) noexcept { return Vector(0, 0, 1); }
	static inline constexpr Vector Down(void) noexcept { return Vector(0, 0, -1); }
	static inline constexpr Vector Right(void) noexcept { return Vector(0, -1, 0); }
	static inline constexpr Vector Left(void) noexcept { return Vector(0, 1, 0); }
	static inline constexpr Vector Forward(void) noexcept { return Vector(1, 0, 0); }
	static inline constexpr Vector Rearward(void) noexcept { return Vector(-1, 0, 0); }

	// Operators
	inline Vector operator-(void) const noexcept { return Vector(-x, -y, -z); }
	inline bool operator==(const Vector &v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	//inline int operator!=(const Vector &v) const { return !(*this == v); } // LUNA: CPP20 - auto generated.
	inline Vector operator+(const Vector &v) const noexcept { return Vector(x + v.x, y + v.y, z + v.z); }
	inline Vector operator-(const Vector &v) const noexcept { return Vector(x - v.x, y - v.y, z - v.z); }
	inline Vector operator*(double fl) const noexcept { return Vector(x * fl, y * fl, z * fl); }
	inline Vector operator/(double fl) const noexcept { fl = 1 / fl; return Vector(x * fl, y * fl, z * fl); }
	inline Vector &operator+=(const Vector &v) noexcept { *this = *this + v; return *this; }
	inline Vector &operator-=(const Vector &v) noexcept { *this = *this - v; return *this; }
	inline Vector &operator*=(double fl) noexcept { *this = *this * fl; return *this; }
	inline Vector &operator/=(double fl) noexcept { *this = *this / fl; return *this; }

	// Methods
	inline void CopyToArray(float *rgfl) const noexcept { rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; }
	inline double LengthSquared(void) const noexcept { return x * x + y * y + z * z; }
	inline double Length(void) const noexcept { return sqrt(LengthSquared()); }
	inline operator float *() noexcept { return &x; } // Vectors will now automatically convert to float * when needed
	inline operator const float *() const noexcept { return &x; } // Vectors will now automatically convert to float * when needed

	inline Vector Normalize(void) const noexcept
	{
		auto const flLength = Length();

		if (flLength <= std::numeric_limits<vec_t>::epsilon())
			return Zero();

		return Vector(x / flLength, y / flLength, z / flLength);
	}

	inline Vector2D Make2D(void) const noexcept { return Vector2D(x, y); }
	inline double LengthSquared2D(void) const noexcept { return x * x + y * y; }
	inline double Length2D(void) const noexcept { return sqrt(LengthSquared2D()); }

	// Members
	vec_t x{}, y{}, z{};
};

export Vector operator*(double fl, const Vector &v) noexcept { return v * fl; }
export double DotProduct(const Vector &a, const Vector &b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z; }
export Vector CrossProduct(const Vector &a, const Vector &b) noexcept { return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

// LUNA: watchout for the freaking marcos.
export using vec3_t = Vector;

export struct Quaternion
{
	constexpr inline Quaternion(void) noexcept = default;
	constexpr inline Quaternion(double W, double X, double Y, double Z) noexcept : a(W), b(X), c(Y), d(Z) {}
	constexpr inline Quaternion(const Quaternion &rhs) noexcept = default;
	inline Quaternion(double yaw, double pitch, double roll) noexcept // yaw (Z), pitch (Y), roll (X)
	{
		yaw *= std::numbers::pi / 180.0;
		pitch *= std::numbers::pi / 180.0;
		roll *= std::numbers::pi / 180.0;

		auto const cy = cos(yaw * 0.5);
		auto const sy = sin(yaw * 0.5);
		auto const cp = cos(pitch * 0.5);
		auto const sp = sin(pitch * 0.5);
		auto const cr = cos(roll * 0.5);
		auto const sr = sin(roll * 0.5);

		a = cr * cp * cy + sr * sp * sy;
		b = sr * cp * cy - cr * sp * sy;
		c = cr * sp * cy + sr * cp * sy;
		d = cr * cp * sy - sr * sp * cy;
	}

	static inline consteval Quaternion Identity(void) noexcept { return Quaternion{ 1, 0, 0, 0 }; }

	inline decltype(auto) Magnitude(void) const noexcept { return sqrt(a * a + b * b + c * c + d * d); }
	inline decltype(auto) Versor(void) const noexcept
	{
		auto const mag = Magnitude();

		if (mag <= std::numeric_limits<double>::epsilon())
			return Identity();

		return Quaternion{ a / mag, b / mag, c / mag, d / mag };
	}

	inline decltype(auto) Real() const noexcept { return a; }
	inline decltype(auto) Pure() const noexcept { return Vector(b, c, d); }

	inline Vector operator* (const Vector &v) const noexcept
	{
		return 2.0 * DotProduct(Pure(), v) * Pure() + (a * a - Pure().LengthSquared()) * v + 2.0 * a * CrossProduct(Pure(), v);
	}

	static inline Quaternion Rotate(const Vector &vecFrom, const Vector &vecTo) noexcept
	{
		auto const vecCross = CrossProduct(vecFrom, vecTo);

		return Quaternion(
			sqrt(vecFrom.LengthSquared() * vecTo.LengthSquared()) + DotProduct(vecFrom, vecTo),
			vecCross.x,
			vecCross.y,
			vecCross.z
		).Versor();
	}

	double a{1}, b{}, c{}, d{};
};
