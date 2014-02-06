#include "vec3i.h"
#include "vec3f.h"
//using namespace mathtool;
namespace lily{
vec3i::vec3i( const vec3f &v )
{
    m_x = (int)v.x();
    m_y = (int)v.y();
    m_z = (int)v.z();
}

vec3i& lily::vec3i::operator=( const vec3f &v )
{
    m_x = (int)v.x();
    m_y = (int)v.y();
    m_z = (int)v.z();
    return *this;
}

vec3i vec3i::index1D_to_index3D_uint64( size_t index1D,const vec3i &size3d )
{
    vec3i pxyz;
    pxyz.setZ(index1D / (size3d.x() * size3d.y()));

    size_t tmp = pxyz.z(); 
    tmp *= size3d.x(); tmp *= size3d.y();

    pxyz.setY((index1D - tmp)/(size_t(size3d.x())) );
    pxyz.setX(index1D % size3d.x());
    return pxyz;
}

vec3i vec3i::index1D_to_index3D( int index1D,const vec3i &size3d )
{
    vec3i pxyz;
    pxyz.setZ(index1D / (size3d.x() * size3d.y()));
    pxyz.setY((index1D - pxyz.z()*size3d.x()*size3d.y())/size3d.x());
    pxyz.setX(index1D % size3d.x());
    return pxyz;
}

}
