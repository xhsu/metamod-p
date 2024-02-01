export module mathlib;

export import <cassert>;
export import <cmath>;
export import <concepts>;
export import <numbers>;

export import vector;


export constexpr bool IS_NAN(std::floating_point auto fl) noexcept { return fl != fl; }

export template <typename T> constexpr
T LinearInterpolation(T const& lhs, T const& rhs, double const t) noexcept
{
	assert(t <= 1 && t >= 0);
	return (lhs * t) + (rhs * (1.0 - t));
}

export template <typename T> constexpr
T SmoothstepInterpolation(T const& lhs, T const& rhs, double t) noexcept
{
	assert(t <= 1 && t >= 0);
	t = (t * t * t * (t * (t * 6 - 15) + 10));
	return (lhs * t) + (rhs * (1.0 - t));
}

export template <typename T> constexpr
T AcceleratedInterpolation(T const& lhs, T const& rhs, double t) noexcept
{
	assert(t <= 1 && t >= 0);
	t = t * t;
	return (lhs * t) + (rhs * (1.0 - t));
}

export template <typename T> constexpr
T DeceleratedInterpolation(T const& lhs, T const& rhs, double t) noexcept
{
	assert(t <= 1 && t >= 0);
	t = 1 - (1 - t) * (1 - t);
	return (lhs * t) + (rhs * (1.0 - t));
}
