#include "vec4i.h"
#include "vec3f.h"
#include "vec4f.h"
//using namespace mathtool;
namespace lily{

vec4f::vec4f( const vec3f& v, float w )
{
    m_x = v.x(); m_y = v.y(); m_z = v.z();
    m_w = w;
}

vec4f::vec4f( const vec4i& v )
{
    m_x = (float)v.x();
    m_y = (float)v.y();
    m_z = (float)v.z();
    m_w = (float)v.w();
}

vec4f& vec4f::operator=( const vec4i &v )
{
    m_x = (float)v.x();
    m_y = (float)v.y();
    m_z = (float)v.z();
    m_w = (float)v.w();
    return *this;
}

}

