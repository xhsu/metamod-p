export module vector;

export import <cmath>;

export import <algorithm>;
export import <numbers>;
export import <string>;

export using vec_t = float;

struct Vector2D;
struct Vector;
struct Angles;
struct Quaternion;

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
	static inline consteval Vector2D Front(void) noexcept { return Vector2D(1, 0); }
	static inline consteval Vector2D Back(void) noexcept { return Vector2D(-1, 0); }

	inline Vector2D operator+(const Vector2D &v) const noexcept { return Vector2D(x + v.x, y + v.y); }
	inline Vector2D operator-(const Vector2D &v) const noexcept { return Vector2D(x - v.x, y - v.y); }
	inline Vector2D operator*(double fl) const noexcept { return Vector2D(x * fl, y * fl); }
	inline Vector2D operator/(double fl) const noexcept { fl = 1 / fl; return Vector2D(x * fl, y * fl); }

	inline double LengthSquared(void) const noexcept { return x * x + y * y; }
	inline double Length(void) const noexcept { return std::sqrt(LengthSquared()); }

	inline Vector2D Normalize(void) const noexcept
	{
		auto const flLength = Length();

		if (flLength <= std::numeric_limits<vec_t>::epsilon())
			return Vector2D();

		return Vector2D(x / flLength, y / flLength);
	}

	// Rotate in counter-clockwise. Angle is in degree.
	inline Vector2D Rotate(const double angle) const noexcept
	{
		const auto a = (angle * std::numbers::pi / 180.0);
		const auto c = std::cos(a);
		const auto s = std::sin(a);

		return Vector2D(
			c * x - s * y,
			s * x + c * y
		);
	}

	vec_t x{}, y{};
};

export double DotProduct(const Vector2D &a, const Vector2D &b) noexcept { return a.x * b.x + a.y * b.y; }
export Vector2D operator*(double fl, const Vector2D &v) noexcept { return v * fl; }

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
	static inline constexpr Vector Front(void) noexcept { return Vector(1, 0, 0); }
	static inline constexpr Vector Back(void) noexcept { return Vector(-1, 0, 0); }

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

	// Conversion
	inline void CopyToArray(float *rgfl) const noexcept { rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; }
	inline operator float *() noexcept { return &x; } // Vectors will now automatically convert to float * when needed
	inline operator const float *() const noexcept { return &x; } // Vectors will now automatically convert to float * when needed

	// Methods as Vector
	inline double LengthSquared(void) const noexcept { return x * x + y * y + z * z; }
	inline double Length(void) const noexcept { return std::sqrt(LengthSquared()); }
	inline Vector Normalize(void) const noexcept
	{
		auto const flLength = Length();

		if (flLength <= std::numeric_limits<vec_t>::epsilon())
			return Zero();

		return Vector(x / flLength, y / flLength, z / flLength);
	}
	inline Angles VectorAngles(void) const noexcept;
	inline double Pitch(void) const noexcept;
	inline double Yaw(void) const noexcept;
	static inline consteval double Roll(void) noexcept { return 0; }	// It make ABSOLUTELY no sense to ask 'roll' of a vector.

	// Methods as Vector2D
	inline Vector2D Make2D(void) const noexcept { return Vector2D(x, y); }
	inline double LengthSquared2D(void) const noexcept { return x * x + y * y; }
	inline double Length2D(void) const noexcept { return std::sqrt(LengthSquared2D()); }

	// Members
	vec_t x{}, y{}, z{};
};

export Vector operator*(double fl, const Vector &v) noexcept { return v * fl; }
export double DotProduct(const Vector &a, const Vector &b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z; }
export Vector CrossProduct(const Vector &a, const Vector &b) noexcept { return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

// LUNA: watchout for the freaking marcos.
export using vec3_t = Vector;

//=========================================================
// Euler Angles
//=========================================================
export struct Angles	// same data-layout as engine's vec3_t
{
	// Construction/destruction
	constexpr inline Angles(void) noexcept = default;	// == Foward()
	constexpr inline Angles(double P, double Y, double R) noexcept : pitch{ (float)P }, yaw{ (float)Y }, roll{ (float)R } {}
	constexpr inline Angles(const Angles &rhs) noexcept = default;

	// Special status
	static inline consteval Angles Upwards(void) noexcept { return Angles(90, 0, 0); }
	static inline consteval Angles Downwards(void) noexcept { return Angles(-90, 0, 0); }
	static inline consteval Angles Rightward(void) noexcept { return Angles(0, 270, 0); }
	static inline consteval Angles Leftward(void) noexcept { return Angles(0, 90, 0); }
	static inline consteval Angles Forward(void) noexcept { return Angles(0, 0, 0); }
	static inline consteval Angles Rearward(void) noexcept { return Angles(0, 180, 0); }

	// Operators
	inline Angles operator-(void) const noexcept { return Angles(-pitch, -yaw, -roll); }
	inline bool operator==(const Angles &rhs) const noexcept { return pitch == rhs.pitch && yaw == rhs.yaw && roll == rhs.roll; }
	inline Angles operator+(const Angles &a) const noexcept { return Angles(pitch + a.pitch, yaw + a.yaw, roll + a.roll); }
	inline Angles operator-(const Angles &a) const noexcept { return Angles(pitch - a.pitch, yaw - a.yaw, roll - a.roll); }
	inline Angles operator*(double fl) const noexcept { return Angles(pitch * fl, yaw * fl, roll * fl); }
	inline Angles operator/(double fl) const noexcept { fl = 1 / fl; return Angles(pitch * fl, yaw * fl, roll * fl); }
	inline Angles &operator+=(const Angles &a) noexcept { pitch += a.pitch; yaw += a.yaw; roll += a.roll; return *this; }
	inline Angles &operator-=(const Angles &a) noexcept { pitch -= a.pitch; yaw -= a.yaw; roll -= a.roll; return *this; }
	inline Angles &operator*=(double fl) noexcept { pitch *= fl; yaw *= fl; roll *= fl; return *this; }
	inline Angles &operator/=(double fl) noexcept { pitch /= fl; yaw /= fl; roll /= fl; return *this; }

	// Conversion
	inline operator float *() noexcept { return &pitch; } // Vectors will now automatically convert to float * when needed
	inline operator const float *() const noexcept { return &pitch; } // Vectors will now automatically convert to float * when needed

	// Radian and Degree
	inline Angles ToRadian() const noexcept { return Angles(pitch * deg_to_rad, yaw * deg_to_rad, roll * deg_to_rad); }
	inline Angles ToDegree() const noexcept { return Angles(pitch * rad_to_deg, yaw * rad_to_deg, roll * rad_to_deg); }

	// Methods
	inline Angles Rationalize(void) const noexcept	// One must call this function before conver to quaternion.
	{
		Angles ret{ *this };

		for (int i = 0; i < 3; ++i)
		{
			while (ret[i] > 360)
				ret[i] -= 360;
			while (ret[i] < -360)
				ret[i] += 360;

			while (ret[i] > 180)
				ret[i] -= 360;
			while (ret[i] < -180)
				ret[i] += 360;
		}

		if (ret.pitch > 90)
		{
			ret.pitch = -(180.f - ret.pitch);
			ret.roll += 180.f;
		}
		else if (ret.pitch < -90)
		{
			ret.pitch = ret.pitch + 180.f;
			ret.roll += 180.f;
		}

		ret.pitch = std::clamp(ret.pitch, -89.99f, 89.99f);	// LUNA: due to the nature of Quaternion, the pitch must fall in the range of (-90, 90)
		//ret.yaw = std::clamp(ret.yaw, -179.99f, 179.99f);	// whereas roll and yaw could be [-180, 180]
		//ret.roll = std::clamp(ret.roll, -179.99f, 179.99f);

		return ret;
	}
	inline std::tuple<Vector, Vector, Vector> AngleVectors() const noexcept
	{
		const auto sp = std::sin(pitch * deg_to_rad), sy = std::sin(yaw * deg_to_rad), sr = std::sin(roll * deg_to_rad);
		const auto cp = std::cos(pitch * deg_to_rad), cy = std::cos(yaw * deg_to_rad), cr = std::cos(roll * deg_to_rad);

		return std::make_tuple(

			// Forward
			Vector(
				cp * cy,	// x
				cp * sy,	// y
				-sp		// z
			),

			// Right
			Vector(
				-(sr * sp * cy) + cr * sy,	// x
				-(sr * sp * sy) - cr * cy,	// y
				-(sr * cp)		// z
			),

			// Up
			Vector(
				cr * sp * cy + sr * sy,	// x
				cr * sp * sy - sr * cy,	// y
				cr * cp		// z
			)
		);
	}
	inline Vector Up(void) const noexcept
	{
		const auto sp = std::sin(pitch * deg_to_rad), sy = std::sin(yaw * deg_to_rad), sr = std::sin(roll * deg_to_rad);
		const auto cp = std::cos(pitch * deg_to_rad), cy = std::cos(yaw * deg_to_rad), cr = std::cos(roll * deg_to_rad);

		return Vector(
			cr * sp * cy + sr * sy,	// x
			cr * sp * sy - sr * cy,	// y
			cr * cp		// z
		);
	}
	inline Vector Down(void) const noexcept
	{
		return -Up();
	}
	inline Vector Right(void) const noexcept
	{
		const auto sp = std::sin(pitch * deg_to_rad), sy = std::sin(yaw * deg_to_rad), sr = std::sin(roll * deg_to_rad);
		const auto cp = std::cos(pitch * deg_to_rad), cy = std::cos(yaw * deg_to_rad), cr = std::cos(roll * deg_to_rad);

		return Vector(
			-(sr * sp * cy) + cr * sy,	// x
			-(sr * sp * sy) - cr * cy,	// y
			-(sr * cp)		// z
		);
	}
	inline Vector Left(void) const noexcept
	{
		return -Right();
	}
	inline Vector Front(void) const noexcept
	{
		const auto sp = std::sin(pitch * deg_to_rad), sy = std::sin(yaw * deg_to_rad);
		const auto cp = std::cos(pitch * deg_to_rad), cy = std::cos(yaw * deg_to_rad);

		return Vector(
			cp * cy,	// x
			cp * sy,	// y
			-sp		// z
		);
	}
	inline Vector Back(void) const noexcept
	{
		return -Front();
	}

	// Members
	vec_t pitch{}, yaw{}, roll{};
	static inline constexpr auto deg_to_rad = std::numbers::pi / 180.0;
	static inline constexpr auto rad_to_deg = 180.0 / std::numbers::pi;
};

inline Angles Vector::VectorAngles(void) const noexcept
{
	Angles angles{};

	if (y == 0 && x == 0)
	{
		angles.yaw = 0;
		if (z > 0)
			angles.pitch = 90;
		else
			angles.pitch = -90;
	}
	else
	{
		angles.yaw = static_cast<float>(std::atan2(y, x) * Angles::rad_to_deg);
		if (angles.yaw < 0)
			angles.yaw += 360;

		angles.pitch = static_cast<float>(std::atan2(z, Length2D()) * Angles::rad_to_deg);
		if (angles.pitch < 0)
			angles.pitch += 360;
	}

	return angles;
}

inline double Vector::Pitch(void) const noexcept
{
	if (y == 0 && x == 0)
	{
		return (z > 0) ? 90 : -90;
	}
	else
	{
		return std::atan2(z, Length2D()) * Angles::rad_to_deg;
	}
}

inline double Vector::Yaw(void) const noexcept
{
	if (y == 0 && x == 0)
	{
		return 0;
	}
	else
	{
		return std::atan2(y, x) * Angles::rad_to_deg;
	}
}

export using ang3_t = Angles;

//=========================================================
// Quaternion
//=========================================================
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

		auto const cy = std::cos(yaw * 0.5);
		auto const sy = std::sin(yaw * 0.5);
		auto const cp = std::cos(pitch * 0.5);
		auto const sp = std::sin(pitch * 0.5);
		auto const cr = std::cos(roll * 0.5);
		auto const sr = std::sin(roll * 0.5);

		a = cr * cp * cy + sr * sp * sy;
		b = sr * cp * cy - cr * sp * sy;
		c = cr * sp * cy + sr * cp * sy;
		d = cr * cp * sy - sr * sp * cy;
	}

	static inline constexpr Quaternion Identity(void) noexcept { return Quaternion{ 1, 0, 0, 0 }; }	// #UPDATE_AT_CPP23 P2564R0 maybe??

	inline decltype(auto) Magnitude(void) const noexcept { return std::sqrt(a * a + b * b + c * c + d * d); }
	inline decltype(auto) Versor(void) const noexcept
	{
		auto const mag = Magnitude();

		if (mag <= std::numeric_limits<double>::epsilon())
			return Identity();

		return Quaternion{ a / mag, b / mag, c / mag, d / mag };
	}

	inline decltype(auto) Real() const noexcept { return a; }
	inline decltype(auto) Pure() const noexcept { return Vector(b, c, d); }

	inline decltype(auto) operator*(const Quaternion &q) const noexcept
	{
		return Quaternion{
			a * q.a - b * q.b - c * q.c - d * q.d,
			b * q.a + a * q.b + c * q.d - d * q.c,
			a * q.c - b * q.d + c * q.a + d * q.b,
			a * q.d + b * q.c - c * q.b + d * q.a
		};
	}
	inline decltype(auto) operator*=(const Quaternion &q) noexcept { return (*this = *this * q); }
	inline decltype(auto) operator* (const Vector &v) const noexcept { return 2.0 * DotProduct(Pure(), v) * Pure() + (a * a - Pure().LengthSquared()) * v + 2.0 * a * CrossProduct(Pure(), v); }

	static inline Quaternion Rotate(const Vector &vecFrom, const Vector &vecTo) noexcept
	{
		auto const vecCross = CrossProduct(vecFrom, vecTo);

		return Quaternion(
			std::sqrt(vecFrom.LengthSquared() * vecTo.LengthSquared()) + DotProduct(vecFrom, vecTo),
			vecCross.x,
			vecCross.y,
			vecCross.z
		).Versor();
	}
	static inline Quaternion AxisAngle(const Vector &vecAxis, double degree) noexcept	// Axis must be a unit vector. In clockwise if works in right-handed coordinate system.
	{
		degree *= std::numbers::pi / 180.0;
		auto const cosine = std::cos(0.5 * degree);
		auto const sine = std::sin(0.5 * degree);

		return Quaternion(cosine,
			vecAxis.x * sine,
			vecAxis.y * sine,
			vecAxis.z * sine
		);
	}
	static inline Quaternion Euler(const Angles &vecAngles) noexcept	// Input must be radian!
	{
		auto const cy = std::cos(vecAngles.yaw * 0.5);
		auto const sy = std::sin(vecAngles.yaw * 0.5);
		auto const cp = std::cos(vecAngles.pitch * 0.5);
		auto const sp = std::sin(vecAngles.pitch * 0.5);
		auto const cr = std::cos(vecAngles.roll * 0.5);
		auto const sr = std::sin(vecAngles.roll * 0.5);

		return Quaternion(
			cr * cp * cy + sr * sp * sy,
			sr * cp * cy - cr * sp * sy,
			cr * sp * cy + sr * cp * sy,
			cr * cp * sy - sr * sp * cy
		);
	}

	inline Angles Euler() const noexcept
	{
		static constexpr auto rad_to_deg = 180.0 / std::numbers::pi;
		Angles vecAngles{};

		// roll (x-axis rotation)
		auto const sinr_cosp = 2 * (a * b + c * d);
		auto const cosr_cosp = 1 - 2 * (b * b + c * c);
		vecAngles.roll = static_cast<vec_t>(std::atan2(sinr_cosp, cosr_cosp) * rad_to_deg);

		// pitch (y-axis rotation)
		auto const sinp = 2 * (a * c - d * b);
		vecAngles.pitch = static_cast<vec_t>(std::asin(std::clamp(sinp, -1.0, 1.0)) * rad_to_deg); // use 90 degrees if out of range

		// yaw (z-axis rotation)
		auto const siny_cosp = 2 * (a * d + b * c);
		auto const cosy_cosp = 1 - 2 * (c * c + d * d);
		vecAngles.yaw = static_cast<vec_t>(std::atan2(siny_cosp, cosy_cosp) * rad_to_deg);

		return vecAngles;
	}

	double a{1}, b{}, c{}, d{};
};
