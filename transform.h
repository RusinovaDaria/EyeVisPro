#pragma once
#include "geometry.h"
#include "poly.h"

// перевод в однородные координаты 
Vec4f to_homogeneous(const Vec3f& v, int is_point);

// перевод в декартовы координаты 
Vec3f to_cartesian(const Vec4f& v);

vec<4, Vec4f> identity_mtrx();

// посылаем матрицу и вектор 
template<typename T> vec<4, T> operator*(const vec<4, vec<4, T>>& m, const vec<4, T>& v) 
{
	vec<4, T> ret
	(
		m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
		m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
		m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
		m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]
	);
	return ret;
}

// посылаем две матрицы
template<typename T> vec<4, vec<4, T>> operator*(const vec<4, vec<4, T>>& m1, const vec<4, vec<4, T>>& m2)
{
	vec<4, vec<4, T>> ret
	(
		vec<4, T>
		(
			m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0] + m1[0][3] * m2[3][0],
			m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1] + m1[0][3] * m2[3][1],
			m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2] + m1[0][3] * m2[3][2],
			m1[0][0] * m2[0][3] + m1[0][1] * m2[1][3] + m1[0][2] * m2[2][3] + m1[0][3] * m2[3][3]
		),

		vec<4, T>
		(
			m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0] + m1[1][3] * m2[3][0],
			m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1] + m1[1][3] * m2[3][1],
			m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2] + m1[1][3] * m2[3][2],
			m1[1][0] * m2[0][3] + m1[1][1] * m2[1][3] + m1[1][2] * m2[2][3] + m1[1][3] * m2[3][3]
		),

		vec<4, T>
		(
			m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0] + m1[2][3] * m2[3][0],
			m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1] + m1[2][3] * m2[3][1],
			m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2] + m1[2][3] * m2[3][2],
			m1[2][0] * m2[0][3] + m1[2][1] * m2[1][3] + m1[2][2] * m2[2][3] + m1[2][3] * m2[3][3]
		),

		vec<4, T>
		(
			m1[3][0] * m2[0][0] + m1[3][1] * m2[1][0] + m1[3][2] * m2[2][0] + m1[3][3] * m2[3][0],
			m1[3][0] * m2[0][1] + m1[3][1] * m2[1][1] + m1[3][2] * m2[2][1] + m1[3][3] * m2[3][1],
			m1[3][0] * m2[0][2] + m1[3][1] * m2[1][2] + m1[3][2] * m2[2][2] + m1[3][3] * m2[3][2],
			m1[3][0] * m2[0][3] + m1[3][1] * m2[1][3] + m1[3][2] * m2[2][3] + m1[3][3] * m2[3][3]
		)
	);
	return ret;
}

// сдвиг объекта
class Movement 
{
public:

	Vec3f mov;
	vec<4, Vec4f> matrix;
	vec<4, Vec4f> matrix_inv;
	
	void fill_matricies()
	{
		matrix[0][0] = 1; matrix[0][1] = 0;  matrix[0][2] = 0;  matrix[0][3] = mov.x;
		matrix[1][0] = 0; matrix[1][1] = 1;  matrix[1][2] = 0;  matrix[1][3] = mov.y;
		matrix[2][0] = 0; matrix[2][1] = 0;  matrix[2][2] = 1;  matrix[2][3] = mov.z;
		matrix[3][0] = 0; matrix[3][1] = 0;  matrix[3][2] = 0;  matrix[3][3] = 1;

		matrix_inv[0][0] = 1; matrix_inv[0][1] = 0;  matrix_inv[0][2] = 0;  matrix_inv[0][3] = -mov.x;
		matrix_inv[1][0] = 0; matrix_inv[1][1] = 1;  matrix_inv[1][2] = 0;  matrix_inv[1][3] = -mov.y;
		matrix_inv[2][0] = 0; matrix_inv[2][1] = 0;  matrix_inv[2][2] = 1;  matrix_inv[2][3] = -mov.z;
		matrix_inv[3][0] = 0; matrix_inv[3][1] = 0;  matrix_inv[3][2] = 0;  matrix_inv[3][3] = 1;
	};

	Movement() : mov(Vec3f(0, 0, 0)) {};
	Movement(float dx, float dy, float dz) : mov(Vec3f(dx, dy, dz))
	{
		fill_matricies();
	};
	Movement(const Vec3f& mv) : mov(mv)
	{
		fill_matricies();
	};

	void setMove(float dx, float dy, float dz)
	{
		mov.x = dx; mov.y = dy; mov.z = dz;
		fill_matricies();
	}
	const Vec3f& getMove() const { return mov; };
	Vec3f move(const Vec3f& v, int is_point, bool inverse = false) const
	{
		Vec4f v_new = Vec4f(v[0], v[1], v[2], is_point);
		
		if (!inverse) v_new = matrix * v_new;
		else v_new = matrix_inv * v_new;

		return Vec3f(v_new[0], v_new[1], v_new[2]);
	};

	vec<4, Vec4f> getMatrix() const
	{
		return matrix;
	};

	vec<4, Vec4f> getMatrix_inv() const
	{
		return matrix_inv;
	};
};


// вращение объекта относительно произвольной точки 
class Rotation
{
public:

	Vec3f angle;
	Vec3f center;

	// матрицы 
	vec<4, Vec4f> matrix_mov;
	vec<4, Vec4f> matrix_x;
	vec<4, Vec4f> matrix_y;
	vec<4, Vec4f> matrix_z;
	vec<4, Vec4f> matrix;

	// обратные матрицы
	vec<4, Vec4f> matrix_mov_inv;
	vec<4, Vec4f> matrix_x_inv;
	vec<4, Vec4f> matrix_y_inv;
	vec<4, Vec4f> matrix_z_inv;
	vec<4, Vec4f> matrix_inv;

	void fill_matricies()
	{
		if (!isZero(angle.x))
		{
			float cosa = cos(angle.x); float sina = sin(angle.x);
			matrix_x[1][1] = cosa; matrix_x[1][2] = -sina; 
			matrix_x[2][1] = sina; matrix_x[2][2] = cosa;  

			matrix_x_inv[1][1] = cosa;  matrix_x_inv[1][2] = sina;
			matrix_x_inv[2][1] = -sina; matrix_x_inv[2][2] = cosa;
		}

		if (!isZero(angle.y))
		{
			float cosa = cos(angle.y); float sina = sin(angle.y);

			matrix_y[0][0] = cosa;  matrix_y[0][2] = sina;
			matrix_y[2][0] = -sina; matrix_y[2][2] = cosa;

			matrix_y_inv[0][0] = cosa; matrix_y_inv[0][2] = -sina;
			matrix_y_inv[2][0] = sina; matrix_y_inv[2][2] = cosa; 
		}

		if (!isZero(angle.z))
		{
			float cosa = cos(angle.z); float sina = sin(angle.z);

			matrix_z[0][0] = cosa;  matrix_z[0][1] = -sina; 
			matrix_z[1][0] = sina;  matrix_z[1][1] = cosa;  

			matrix_z_inv[0][0] = cosa;  matrix_z_inv[0][1] = sina;
			matrix_z_inv[1][0] = -sina; matrix_z_inv[1][1] = cosa;
		}
	
		matrix_mov[0][3] = -center.x;
		matrix_mov[1][3] = -center.y;
		matrix_mov[2][3] = -center.z;

		matrix_mov_inv[0][3] = center.x;
		matrix_mov_inv[1][3] = center.y;
		matrix_mov_inv[2][3] = center.z;

		count_rotation_matrix();
	};

	void count_rotation_matrix()
	{
		matrix = matrix * matrix_mov_inv;
		if (!isZero(angle.x)) { matrix = matrix * matrix_x; }
		if (!isZero(angle.z)) { matrix = matrix * matrix_z; }
		if (!isZero(angle.y)) { matrix = matrix * matrix_y; }
		matrix = matrix * matrix_mov;

		matrix_inv = matrix_inv * matrix_mov_inv;
		if (!isZero(angle.y)) { matrix_inv = matrix_inv * matrix_y_inv; }
		if (!isZero(angle.z)) { matrix_inv = matrix_inv * matrix_z_inv; }
		if (!isZero(angle.x)) { matrix_inv = matrix_inv * matrix_x_inv; }
		matrix_inv = matrix_inv * matrix_mov;
	}

	// центр вращения и углы вокруг каждой из осей 
	Rotation() : center(Vec3f(0,0,0)), angle(Vec3f(0, 0, 0)), 
		matrix( identity_mtrx()), 
		matrix_x( identity_mtrx()), 
		matrix_y( identity_mtrx()), 
		matrix_z( identity_mtrx()), 
		matrix_mov( identity_mtrx()), 

		matrix_inv( identity_mtrx()),
		matrix_x_inv( identity_mtrx()),
		matrix_y_inv( identity_mtrx()),
		matrix_z_inv( identity_mtrx()),
		matrix_mov_inv(identity_mtrx())
	{};

	Rotation(float ax, float ay, float az) : center(Vec3f(0, 0, 0)), angle(Vec3f(ax, ay, az)),
		matrix(identity_mtrx()),
		matrix_x(identity_mtrx()),
		matrix_y(identity_mtrx()),
		matrix_z(identity_mtrx()),
		matrix_mov(identity_mtrx()),

		matrix_inv(identity_mtrx()),
		matrix_x_inv(identity_mtrx()),
		matrix_y_inv(identity_mtrx()),
		matrix_z_inv(identity_mtrx()),
		matrix_mov_inv(identity_mtrx())
	{ fill_matricies(); };

	Rotation(const Vec3f& c, float ax, float ay, float az) : center(c), angle(Vec3f(ax, ay, az)),
		matrix(identity_mtrx()),
		matrix_x(identity_mtrx()),
		matrix_y(identity_mtrx()),
		matrix_z(identity_mtrx()),
		matrix_mov(identity_mtrx()),

		matrix_inv(identity_mtrx()),
		matrix_x_inv(identity_mtrx()),
		matrix_y_inv(identity_mtrx()),
		matrix_z_inv(identity_mtrx()),
		matrix_mov_inv(identity_mtrx())
	{ fill_matricies(); };

	Rotation(const Vec3f& c, const Vec3f& a) : center(c), angle(a),
		matrix(identity_mtrx()),
		matrix_x(identity_mtrx()),
		matrix_y(identity_mtrx()),
		matrix_z(identity_mtrx()),
		matrix_mov(identity_mtrx()),

		matrix_inv(identity_mtrx()),
		matrix_x_inv(identity_mtrx()),
		matrix_y_inv(identity_mtrx()),
		matrix_z_inv(identity_mtrx()),
		matrix_mov_inv(identity_mtrx())
	{
		fill_matricies();
	};

	void setParameters(const Vec3f& c, const Vec3f& a)
	{
		center = c;
		angle = a;
		fill_matricies();
	}

	vec<4, Vec4f> getMatrix() const
	{
		return matrix;
	};

	vec<4, Vec4f> getMatrix_inv() const
	{
		return matrix_inv;
	};
};
