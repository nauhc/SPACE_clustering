#ifndef _MATHTOOL_H_
#define _MATHTOOL_H_
#include <stdint.h>
#include "vec3f.h"
#include "vec3i.h"

namespace lily{

inline float fminf( float a, float b )
{
    return a < b ? a : b;
}

inline float fmaxf(float a, float b)
{
    return a > b ? a : b;
}

inline int maxi(int a, int b)
{
    return a > b ? a : b;
}

inline int mini(int a, int b)
{
    return a < b ? a : b;
}

inline float lerp(float a, float b, float t)
{
    return a + t*(b-a);
}
inline vec3f lerp(const vec3f &a, const vec3f &b, float t)
{
    return a + t*(b-a);
}

//return the component-wise min
vec3f fminf(const vec3f &a,const vec3f &b);
//return the component-wise max
vec3f fmaxf(const vec3f &a,const vec3f &b);
//return the component-wise min
vec3i mini(const vec3i &a,const vec3i &b);
//return the component-wise max
vec3i maxi(const vec3i &a,const vec3i &b);
}
#endif