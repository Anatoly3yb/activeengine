#ifndef TRANSFORM_INTERPOLATOR_H
#define TRANSFORM_INTERPOLATOR_H

#include "core/math/math_defs.h"
#include "core/math/quat.h"
#include "core/math/transform.h"
#include "core/math/vector3.h"

// Keep all the functions for fixed timestep interpolation together.
// There are two stages involved:
// Finding a method, for determining the interpolation method between two
// keyframes (which are physics ticks).
// And applying that pre-determined method.

// Pre-determining the method makes sense because it is expensive and often
// several frames may occur between each physics tick, which will make it cheaper
// than performing every frame.

struct Transform2D;

class TransformInterpolator {
public:
	enum Method : unsigned int {
		INTERP_LERP,
		INTERP_SLERP,
		INTERP_SCALED_SLERP,
	};

private:
	static real_t _vec3_normalize(Vector3 &p_vec);
	static Vector3 _basis_orthonormalize(Basis &r_basis);
	static real_t vec3_sum(const Vector3 &p_pt) { return p_pt.x + p_pt.y + p_pt.z; }
	static Method _test_basis(Basis p_basis, bool r_needed_normalize, Quat &r_quat);
	static Basis _basis_slerp_unchecked(Basis p_from, Basis p_to, real_t p_fraction);
	static Quat _quat_slerp_unchecked(const Quat &p_from, const Quat &p_to, real_t p_fraction);
	static Quat _basis_to_quat_unchecked(const Basis &p_basis);
	static bool _basis_is_orthogonal(const Basis &p_basis, real_t p_epsilon = 0.01f);
	static bool _basis_is_orthogonal_any_scale(const Basis &p_basis);
	static bool _sign(real_t p_val) { return p_val >= 0; }

	static void interpolate_basis_linear(const Basis &p_prev, const Basis &p_curr, Basis &r_result, real_t p_fraction);
	static void interpolate_basis_scaled_slerp(Basis p_prev, Basis p_curr, Basis &r_result, real_t p_fraction);

public:
	// Generic functions, use when you don't know what method should be used, e.g. from gdscript.
	// These will be slower.
	static void interpolate_transform(const Transform &p_prev, const Transform &p_curr, Transform &r_result, real_t p_fraction);
	static void interpolate_basis(const Basis &p_prev, const Basis &p_curr, Basis &r_result, real_t p_fraction);
	static void interpolate_transform_2d(const Transform2D &p_prev, const Transform2D &p_curr, Transform2D &r_result, real_t p_fraction);

	// Optimized function when you know ahead of time the method
	static void interpolate_transform_via_method(const Transform &p_prev, const Transform &p_curr, Transform &r_result, real_t p_fraction, Method p_method);
	static void interpolate_basis_via_method(const Basis &p_prev, const Basis &p_curr, Basis &r_result, real_t p_fraction, Method p_method);

	static real_t checksum_transform(const Transform &p_transform);
	static Method find_method(const Basis &p_a, const Basis &p_b);
};

#endif // TRANSFORM_INTERPOLATOR_H
