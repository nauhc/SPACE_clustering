#include "vec3f.h"
#include "vec3i.h"
//using namespace mathtool;
namespace lily{

vec3f::vec3f( const vec3i& v )
{
    m_x = (float)v.x();
    m_y = (float)v.y();
    m_z = (float)v.z();
}

vec3f& lily::vec3f::operator=( const vec3i &v )
{
    m_x = (float)v.x();
    m_y = (float)v.y();
    m_z = (float)v.z();
    return *this;
}

}

