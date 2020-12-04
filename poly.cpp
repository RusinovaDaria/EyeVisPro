// poly34.cpp : solution of cubic and quartic equation
// (c) Khashin S.I. http://math.ivanovo.ac.ru/dalgebra/Khashin/index.html
// khash2 (at) gmail.com
// Thanks to Alexandr Rakhmanin <rakhmanin (at) gmail.com>
// public domain
//
#include <math.h>

#include "poly.h"		   // solution of cubic and quartic equation
#define	TwoPi  6.28318530717958648
const float eps=1e-14;

//=============================================================================
// _root3, root3 from http://prografix.narod.ru
//=============================================================================
static float _root3 ( float x )
{
    float s = 1.;
    while ( x < 1. )
    {
        x *= 8.;
        s *= 0.5;
    }
    while ( x > 8. )
    {
        x *= 0.125;
        s *= 2.;
    }
    float r = 1.5;
    r -= 1./3. * ( r - x / ( r * r ) );
    r -= 1./3. * ( r - x / ( r * r ) );
    r -= 1./3. * ( r - x / ( r * r ) );
    r -= 1./3. * ( r - x / ( r * r ) );
    r -= 1./3. * ( r - x / ( r * r ) );
    r -= 1./3. * ( r - x / ( r * r ) );
    return r * s;
}

float root3 ( float x )
{
    if ( x > 0 ) return _root3 ( x ); else
    if ( x < 0 ) return-_root3 (-x ); else
    return 0.;
}

bool isZero(float x)
{
	return (x < 1e-6) && (x > -1e-6);
}


// solve equation x^2 + a*x + b = 0
// return 2: 2 real roots x[0], x[1]
// return 1: 1 real root x[0]
// return 0: no roots
int   SolveP2(Vec2f coeff, Vec2f& x) {	
	
	float a = coeff[0];
	float b = coeff[1];
	
	float D = 0.25 * a * a - b;
	if (isZero(D))
	{
		x[0] = -0.5 * a;
		return 1;
	}
	else if (D > 0)
	{
		D = sqrt(D);
		x[0] = -0.5 * a + D;
		x[1] = -0.5 * a - D;
		return 2;
	}

	return 0;
}


//---------------------------------------------------------------------------


// solve cubic equation x^3 + a*x^2 + b*x + c = 0
// In case 3 real roots: => x[0], x[1], x[2], return 3
//         2 real roots: x[0], x[1],          return 2
//         1 real root : x[0],                return 1
int   SolveP3(Vec3f coeff, Vec3f& x) {	
	float a = coeff[0];
	float b = coeff[1];
	float c = coeff[2];

	//std::cout << a << " " << b << " " << c << "\n";
	 
	double a2 = a * a;
	double q = (a2 - 3 * b) / 9;
	double r = (a * (2 * a2 - 9 * b) + 27 * c) / 54;

	// equation x^3 + q*x + r = 0
	double r2 = r * r;
	double q3 = q * q * q;
	double A, B;
	if (r2 <= q3 + eps) {

		double phi = acos(r / sqrt(q3)) / 3;

		//if (t < -1) t = -1;
		//if (t > 1) t = 1;
		//t = acos(t);

		a /= 3; 
		q = -2 * sqrt(q);
		x[0] = q * cos(phi) - a;
		x[1] = q * cos(phi + (TwoPi/3)) - a;
		x[2] = q * cos(phi - (TwoPi/3)) - a;

		return(3);
	}
	else {

		//A =-pow(fabs(r)+sqrt(r2-q3),1./3); 
		A = -root3(fabs(r) + sqrt(r2 - q3));
		if (r < 0) A = -A;
		B = (A == 0 ? 0 : B = q / A);

		a /= 3;
		x[0] = (A + B) - a;
		x[1] = -0.5 * (A + B) - a;
		x[2] = 0.5 * sqrt(3.) * (A - B);
		if (fabs(x[2]) < eps) { x[2] = x[1]; return(2); }
		return(1);
	}
}


//---------------------------------------------------------------------------


// solve equation x^4 + b*x^2 + d = 0
int   SolveP4Bi(Vec4f& x, float b, float d)
{
	float D = b*b-4*d;
	if( D >= 0 ) 
	{
		float sD = sqrt(D);
		float x1 = (-b+sD)/2;
		float x2 = (-b-sD)/2;	// x2 <= x1
		
		// 0 <= x2 <= x1, 4 real roots
		if( x2 >= 0 )			
		{
			float sx1 = sqrt(x1);
			float sx2 = sqrt(x2);
			x[0] = -sx1;
			x[1] =  sx1;
			x[2] = -sx2;
			x[3] =  sx2;
			return 4;
		}

		// now x2 < 0 <= x1, 2 real roots 
			float sx1 = sqrt( x1);
			float sx2 = sqrt(-x2);
			x[0] = -sx1;
			x[1] =  sx1;
			return 2;
	} 

	// no real roots
	return 0;
} 

#define SWAP(a,b) { t=b; b=a; a=t; }
static void  dblSort3(float &a, float &b, float &c) // make: a <= b <= c
{
	float t;
	if( a>b ) SWAP(a,b);	// now a<=b
	if( c<b ) {
		SWAP(b,c);			// now a<=b, b<=c
		if( a>b ) SWAP(a,b);// now a<=b
	}
}

void  CSqrt(float x, float y, float& a, float& b) // returns:  a+i*s = sqrt(x+i*y)
{
	float r = sqrt(x * x + y * y);
	if (y == 0) {
		r = sqrt(r);
		if (x >= 0) { a = r; b = 0; }
		else { a = 0; b = r; }
	}
	else {		// y != 0
		a = sqrt(0.5 * (x + r));
		b = 0.5 * y / a;
	}
}

// solve equation x^4 + b*x^2 + c*x + d
int   SolveP4De(Vec4f& x, float b, float c, float d)
{
	//if( c==0 ) return SolveP4Bi(x,b,d); // After that, c!=0
	if( fabs(c)<1e-14*(fabs(b)+fabs(d)) ) return SolveP4Bi(x,b,d); // After that, c!=0

	Vec3f x_3;
	int res3 = SolveP3( x_3, Vec3f(2*b, b*b-4*d, -c*c));	// solve resolvent
	x[0] = x_3[0];
	x[1] = x_3[1];
	x[2] = x_3[2];

	// by Viet theorem:  x1*x2*x3=-c*c not equals to 0, so x1!=0, x2!=0, x3!=0
	if( res3>1 )	// 3 real roots, 
	{				
		dblSort3(x[0], x[1], x[2]);	// sort roots to x[0] <= x[1] <= x[2]
		// Note: x[0]*x[1]*x[2]= c*c > 0
		if(x[0] > 0) // all roots are positive
		{
			float sz1 = sqrt(x[0]);
			float sz2 = sqrt(x[1]);
			float sz3 = sqrt(x[2]);
			// Note: sz1*sz2*sz3= -c (and not equal to 0)
			if( c>0 )
			{
				x[0] = (-sz1 -sz2 -sz3)/2;
				x[1] = (-sz1 +sz2 +sz3)/2;
				x[2] = (+sz1 -sz2 +sz3)/2;
				x[3] = (+sz1 +sz2 -sz3)/2;
				return 4;
			}
			// now: c<0
			x[0] = (-sz1 -sz2 +sz3)/2;
			x[1] = (-sz1 +sz2 -sz3)/2;
			x[2] = (+sz1 -sz2 -sz3)/2;
			x[3] = (+sz1 +sz2 +sz3)/2;
			return 4;
		} // if( x[0] > 0) // all roots are positive
		
		// no real roots
		return 0;
	} 
	
	
	if (x[0] < 0) x[0] = 0;
	float sz1 = sqrt(x[0]);
	float szr, szi;
	
	CSqrt(x[1], x[2], szr, szi);  // (szr+i*szi)^2 = x[1]+i*x[2]
	if( c>0 )	// sign = -1
	{
		x[0] = -sz1/2-szr;			// 1st real root
		x[1] = -sz1/2+szr;			// 2nd real root
		return 2;
	}

	// now: c<0 , sign = +1
	x[0] = sz1/2-szr;			// 1st real root
	x[1] = sz1/2+szr;			// 2nd real root
	return 2;
} 

float N4Step(float x, float a,float b,float c,float d)	// one Newton step for x^4 + a*x^3 + b*x^2 + c*x + d
{
	float fxs= ((4*x+3*a)*x+2*b)*x+c;	// f'(x)
	if (fxs == 0) return x;	//return 1e99; <<-- FIXED!
	float fx = (((x+a)*x+b)*x+c)*x+d;	// f(x)
	return x - fx/fxs;
} 
//-----------------------------------------------------------------------------
// x - array of size 4
// return 4: 4 real roots x[0], x[1], x[2], x[3], possible multiple roots
// return 2: 2 real roots x[0], x[1] and complex x[2]±i*x[3], 
// return 0: no roots 
int   SolveP4(Vec4f coeff, Vec4f& x) {	// solve equation x^4 + a*x^3 + b*x^2 + c*x + d by Dekart-Euler method
	// move to a=0:

	float a = coeff[0];
	float b = coeff[1];
	float c = coeff[2];
	float d = coeff[3];

	float d1 = d + 0.25*a*( 0.25*b*a - 3./64*a*a*a - c);
	float c1 = c + 0.5*a*(0.25*a*a - b);
	float b1 = b - 0.375*a*a;
	int res = SolveP4De( x, b1, c1, d1);
	if( res==4) { x[0]-= a/4; x[1]-= a/4; x[2]-= a/4; x[3]-= a/4; }
	else if (res==2) { x[0]-= a/4; x[1]-= a/4; x[2]-= a/4; }
	else             { x[0]-= a/4; x[2]-= a/4; }
	// one Newton step for each real root:
	if( res>0 )
	{
		x[0] = N4Step(x[0], a,b,c,d);
		x[1] = N4Step(x[1], a,b,c,d);
	}
	if( res>2 )
	{
		x[2] = N4Step(x[2], a,b,c,d);
		x[3] = N4Step(x[3], a,b,c,d);
	}
	return res;
}