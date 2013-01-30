/////////////////////////////////////////
//   模块:  vector.h
//   功能:  二维和三维向量定义
//   作者:   
/////////////////////////////////////////
#pragma once

typedef float vec_t;
/*
struct vect2_t
{
public:
	vec_t x,y;
	vect2_t () { x = 0.0f; y = 0.0f; }
	vect2_t (const vect2_t& s)
	{
	   x = s.x;
	   y = s.y;
	}
	inline vect2_t& operator = ( const vect2_t& Value )
	{
		memcpy( this, &Value, sizeof( vect2_t ) );
		return *this;
	}
	bool operator!=( const struct vect2_t &other ) const;

};

inline bool vect2_t::operator!=( const vect2_t &other ) const
{
	return x != other.x || y != other.y;
}

struct vect3_t : public vect2_t
{
	vec_t z;
	vect3_t () { x = 0.0f; y = 0.0f; z = 0.0f; }
	vect3_t (const vect3_t& s){
		x = s.x;
		y = s.y;
		z = s.z;
	}
	inline vect3_t& operator = ( const vect3_t& Value )
	{
		memcpy( this, &Value, sizeof( vect3_t ) );
		return *this;
	}
	inline void Set( float sx, float sy, float sz )
	{
		x = sx;
		y = sy;
		z = sz;
	}
};
*/
struct VertexCord
{
	float x, y;
	union				/* 因Z处理,使用union */
	{
		float z;
		int  iz;
	};

   float weighttotal;
};


///////////////////////////////////////////////////////////////////////////////
#include "vector3d.h"
extern void CrossProduct ( const float *v1, const float *v2, float *cross );
/*
inline void CrossProduct (const float* v1, const float* v2, float* cross)
{

	cross[0] = v1[1]*v2[2] - v1[2]*v2[1];
	cross[1] = v1[2]*v2[0] - v1[0]*v2[2];
	cross[2] = v1[0]*v2[1] - v1[1]*v2[0];
}
*/
inline float VtorNormalize( Vector &vec )
{

	float radius = sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	//TODO: ...

	// FLT_EPSILON is added to the radius to eliminate the possibility of divide by zero.
	float iradius = 1.f / ( radius + FLT_EPSILON );
	
	vec.x *= iradius;
	vec.y *= iradius;
	vec.z *= iradius;

	return radius;
}

inline void Vector2Scale2( Vector *in, float scale, Vector *out)
{
	out->x = in->x *scale;
	out->y = in->y *scale;
}

inline void Vector2Add2( Vector *out, Vector *vecta, Vector *vectb )
{
	out->x = vecta->x + vectb->x;
	out->y = vecta->y + vectb->y;

}
inline void Vector2Subtract2( Vector *veca, Vector *vecb, Vector *out)
{
	out->x = veca->x - vecb->x;
	out->y = veca->y - vecb->y;

}

inline  vec_t Vector2length2( Vector *v )
{
	return (vec_t)sqrtf(v->x * v->x + v->y * v->y);
}

inline vec_t Vector2Distance2( Vector *veca, Vector *vecb )
{
	Vector delta;
	Vector2Subtract2( veca, vecb, &delta );
	return Vector2length2(&delta);
}

/*
//-----------------------------------------------------------------------------
// Quantion
//-----------------------------------------------------------------------------


class RadianEuler;

class Quaternion				// same data-layout as engine's vec4_t,
{								//		which is a vec_t[4]
public:
	inline Quaternion(void)							{ }
	inline Quaternion(RadianEuler const &angle);	// evil auto type promotion!!!

	inline void Init(vec_t ix=0.0f, vec_t iy=0.0f, vec_t iz=0.0f, vec_t iw=0.0f)	{ x = ix; y = iy; z = iz; w = iw; }

	bool IsValid() const;

	// array access...
	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	vec_t x, y, z, w;
};


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

inline vec_t& Quaternion::operator[](int i)
{
	Assert( (i >= 0) && (i < 4) );
	return ((vec_t*)this)[i];
}

inline vec_t Quaternion::operator[](int i) const
{
	Assert( (i >= 0) && (i < 4) );
	return ((vec_t*)this)[i];
}

//-----------------------------------------------------------------------------
// Radian Euler QAngle aligned to axis (NOT ROLL/PITCH/YAW)
//-----------------------------------------------------------------------------

class RadianEuler
{
public:
	inline RadianEuler(void)							{ }
	inline RadianEuler(vec_t X, vec_t Y, vec_t Z)		{ x = X; y = Y; z = Z; }
	inline RadianEuler(Quaternion const &q);	// evil auto type promotion!!!

	// Initialization
	inline void Init(vec_t ix=0.0f, vec_t iy=0.0f, vec_t iz=0.0f)	{ x = ix; y = iy; z = iz; }

	bool IsValid() const;

	// array access...
	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	vec_t x, y, z;
};


extern void AngleQuaternion( RadianEuler const &angles, Quaternion &qt );
extern void QuaternionAngles( Quaternion const &q, RadianEuler &angles );
inline Quaternion::Quaternion(RadianEuler const &angle)
{
	AngleQuaternion( angle, *this );
}

inline bool Quaternion::IsValid() const
{
	return IsFinite(x) && IsFinite(y) && IsFinite(z) && IsFinite(w);
}

inline RadianEuler::RadianEuler(Quaternion const &q)
{
	QuaternionAngles( q, *this );
}
*/


