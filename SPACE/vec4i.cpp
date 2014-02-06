#include "vec4i.h"
#include "vec4f.h"
//using namespace mathtool;
namespace lily{

vec4i::vec4i( const vec4f &v )
{
    m_x = (int)v.x();
    m_y = (int)v.y();
    m_z = (int)v.z();
    m_w = (int)v.w();
}

vec4i& vec4i::operator=( const vec4f &v )
{
    m_x = (int)v.x();
    m_y = (int)v.y();
    m_z = (int)v.z();
    m_w = (int)v.w();
    return *this;
}

}
