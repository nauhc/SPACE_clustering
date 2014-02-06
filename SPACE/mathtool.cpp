#include "mathtool.h"
namespace lily{
vec3f fminf(const vec3f &a,const vec3f &b )
{
    return vec3f(fminf(a.x(),b.x()),
        fminf(a.y(),b.y()),
        fminf(a.z(),b.z()));
}

vec3f fmaxf(const vec3f &a,const vec3f &b )
{
    return vec3f(fmaxf(a.x(),b.x()),
                 fmaxf(a.y(),b.y()),
                 fmaxf(a.z(),b.z()));
}

vec3i mini(const vec3i &a,const vec3i &b )
{
    return vec3i(fminf(a.x(),b.x()),
        fminf(a.y(),b.y()),
        fminf(a.z(),b.z()));
}

vec3i maxi(const vec3i &a,const vec3i &b )
{
    return vec3i(maxi(a.x(),b.x()),
                 maxi(a.y(),b.y()),
                 maxi(a.z(),b.z()));
}
}