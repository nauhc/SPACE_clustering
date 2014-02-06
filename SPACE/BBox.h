#ifndef _BBOX_H_
#define _BBOX_H_

#pragma once
#include "vec3f.h"
#include "constant.h"

namespace lily{

class BBox{
public:
    vec3f pMin;
    vec3f pMax;
    //float  m_dist
    BBox(void);
    BBox(const vec3f &p) : pMin(p), pMax(p) { }
    //c: center of the bbox,
    //r: radius of the bbox.
    BBox(const vec3f& c, float r);
    //lower and upper corner of the bbox.
    BBox(const vec3f& p1, const vec3f& p2);
    BBox Union(const vec3f& pt) const;
    BBox Union(const BBox& box) const;
    vec3f getDimension() const;
    bool Overlap(const vec3f& p ) const;
    bool Overlap(const BBox& box) const;
    bool Overlap(const BBox& box, float tolerance) const;
    //if a point is inside the box.
    bool Inside(const vec3f& pt) const;
    void Expand(float delta);
    float SurfaceArea() const;
    float Volume()const;
    int   MaximumExtent()  const;
    float MaximumExtentf() const;
    vec3f LerpPt(float tx, float ty, float tz) const;
    //returns the position of a point relative to the corners of the box,
    //where a point at the minimum corner has offset (0, 0, 0), a point at the maximum corner
    //has offset (1, 1, 1).
    vec3f Offset(const vec3f& p) const;
    vec3f Center() const;
    //Radius() only make sense when the box is assumed as cube.
    float BoxRadius() const
    {
        return MaximumExtentf()*0.5f;
    }

    float SphericalRadius() const
    {
        return BoxRadius() * SQRT_3;
    }
friend BBox& operator << (BBox& bbox, const vec3f& v)
{
    bbox = bbox.Union(v);
    return bbox;
}

friend BBox& operator << (BBox& bbox, const BBox& bbox2)
{
    bbox = bbox.Union(bbox2);
    return bbox;
}

friend std::ostream& operator << (std::ostream& os,const BBox& b)
{
    os<<"["<<b.pMin<<", "<<b.pMax<<"]\n";
    return os;
}

};
};//end of namespace
#endif

