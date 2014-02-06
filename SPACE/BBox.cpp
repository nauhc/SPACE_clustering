#include "BBox.h"
#include "mathtool.h"
#include "constant.h"

namespace lily{
BBox::BBox( void )
    :pMin(FLOAT_MAX),pMax(-FLOAT_MAX)
{
}

BBox::BBox( const vec3f& c, float r )
{
    pMin = c - r;
    pMax = c + r;
}

BBox::BBox( const vec3f& p1, const vec3f& p2 )
{
    pMin = lily::fminf(p1,p2);
    pMax = lily::fmaxf(p1,p2);
}

BBox BBox::Union( const vec3f& pt ) const
{
    BBox ret = *this;
    ret.pMin = lily::fminf(pMin, pt);
    ret.pMax = lily::fmaxf(pMax, pt);
    return ret;
}

BBox BBox::Union( const BBox& box ) const
{
    BBox ret = *this;
    ret.pMin = fminf(pMin, box.pMin);
    ret.pMax = fmaxf(pMax, box.pMax);
    return ret;
}

bool BBox::Overlap( const vec3f& p ) const
{
    bool x = (pMax.x() >= p.x()) && (pMin.x() <= p.x());
    bool y = (pMax.y() >= p.y()) && (pMin.y() <= p.y());
    bool z = (pMax.z() >= p.z()) && (pMin.z() <= p.z());
    return (x && y && z);
}

bool BBox::Overlap( const BBox& b ) const
{
    bool x = (pMax.x() >= b.pMin.x()) && (pMin.x() <= b.pMax.x());
    bool y = (pMax.y() >= b.pMin.y()) && (pMin.y() <= b.pMax.y());
    bool z = (pMax.z() >= b.pMin.z()) && (pMin.z() <= b.pMax.z());
    return (x && y && z);
}

bool BBox::Overlap( const BBox& b, float tolerance) const
{
    bool x = ((pMax.x() - b.pMin.x()) > tolerance ) && (tolerance < (b.pMax.x() - pMin.x()));
    bool y = ((pMax.y() - b.pMin.y()) > tolerance ) && (tolerance < (b.pMax.y() - pMin.y()));
    bool z = ((pMax.z() - b.pMin.z()) > tolerance ) && (tolerance < (b.pMax.z() - pMin.z()));
    return (x && y && z);
}

bool BBox::Inside( const vec3f& pt) const
{
    return (pt.x() >= pMin.x() && pt.x() <= pMax.x() &&
            pt.y() >= pMin.y() && pt.y() <= pMax.y() &&
            pt.z() >= pMin.z() && pt.z() <= pMax.z());
}

void BBox::Expand( float delta )
{
    pMax += delta;
    pMin -= delta;
}

float BBox::SurfaceArea() const
{
    vec3f d = pMax - pMin;
    return 2.f * (d.x() * d.y() + d.x() * d.z() + d.y() * d.z());
}

float BBox::Volume() const
{
    vec3f d = pMax - pMin;
    return d.x() * d.y() * d.z();
}

int BBox::MaximumExtent() const {
    vec3f diag = pMax - pMin;
    if (diag.x() > diag.y() && diag.x() > diag.z())
        return 0;
    else if (diag.y() > diag.z())
        return 1;
    else
        return 2;
}
float BBox::MaximumExtentf() const {
    return max_extend2f(pMax, pMin);
}
vec3f BBox::LerpPt( float tx, float ty, float tz ) const
{
    return vec3f(lerp(pMin.x(), pMax.x(), tx),
                 lerp(pMin.y(), pMax.y(), ty),
                 lerp(pMin.z(), pMax.z(), tz));
}

vec3f BBox::Offset( const vec3f& p ) const
{
    return (p - pMin) / (pMax - pMin);
}

vec3f BBox::Center() const
{
    return 0.5f * ( pMax + pMin );
}

vec3f BBox::getDimension() const
{
    return (pMax - pMin);
}
}//end of namespace geometry

