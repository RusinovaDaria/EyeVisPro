// poly34.h : solution of cubic and quartic equation
// (c) Khashin S.I. http://math.ivanovo.ac.ru/dalgebra/Khashin/index.html
// khash2 (at) gmail.com

#include "geometry.h"

bool isZero(float x);

// x - array of size 2
// return 2: 2 real roots x[0], x[1]
// return 0: no roots
int   SolveP2(Vec2f coeff, Vec2f& x);			// solve equation x^2 + a*x + b = 0

// x - array of size 3
// return 3: 3 real roots x[0], x[1], x[2]
// return 1: 1 real root x[0] and pair of complex roots: x[1]켲*x[2]
int   SolveP3(Vec3f coeff, Vec3f& x);			// solve cubic equation x^3 + a*x^2 + b*x + c = 0

// x - array of size 4
// return 4: 4 real roots x[0], x[1], x[2], x[3], possible multiple roots
// return 2: 2 real roots x[0], x[1] and complex x[2]켲*x[3], 
// return 0: no roots
int   SolveP4(Vec4f coeff, Vec4f& x);	// solve equation x^4 + a*x^3 + b*x^2 + c*x + d = 0 by Dekart-Euler method

// x - array of size 5
// return 5: 5 real roots x[0], x[1], x[2], x[3], x[4], possible multiple roots
// return 3: 3 real roots x[0], x[1], x[2] and complex x[3]켲*x[4], 
// return 1: 1 real root x[0] and two pair of complex roots: x[1]켲*x[2],  x[3]켲*x[4], 
//int   SolveP5(double *x, double a, double b, double c, double d, double e);	// solve equation x^5 + a*x^4 + b*x^3 + c*x^2 + d*x + e = 0

//-----------------------------------------------------------------------------
// And some additional functions for internal use.
// Your may remove this definitions from here
int   SolveP4Bi(Vec4f& x, float b, float d);				// solve equation x^4 + b*x^2 + d = 0
int   SolveP4De(Vec4f& x, float b, float c, float d);	// solve equation x^4 + b*x^2 + c*x + d = 0
void  CSqrt(float x, float y, float& a, float& b);		// returns as a+i*s,  sqrt(x+i*y)
float N4Step(float x, float a, float b, float c, float d);// one Newton step for x^4 + a*x^3 + b*x^2 + c*x + d

