#ifndef _VEC4I_H_
#define _VEC4I_H_
#pragma once
#include <cmath>
#include <iostream>
using namespace std;

namespace lily{
class vec4f;

class vec4i
{
private:
    union{
        struct{
            int m_x, m_y, m_z, m_w;
        };
        struct{
            int m_v[4];
        };
    };

public:
    vec4i(void):m_x(0),m_y(0),m_z(0), m_w(0){};
    vec4i(int x, int y, int z, int w):m_x(x),m_y(y),m_z(z), m_w(w){};
    explicit vec4i(int s):m_x(s),m_y(s),m_z(s), m_w(s){};
    explicit vec4i(const vec4f &v);
    explicit vec4i(const int vs[4]):m_x(vs[0]),m_y(vs[1]),m_z(vs[2]), m_w(vs[3]){};

    int x() const {return m_x;}
    int y() const {return m_y;}
    int z() const {return m_z;}
    int w() const {return m_w;}
    int v(int i) const { return m_v[i];}
    void  setX(int x) {m_x = x;}
    void  setY(int y) {m_y = y;}
    void  setZ(int z) {m_z = z;}
    void  setW(int w) {m_w = w;}
    int max_extend1i() const{
        int dx, dy, dz, dw, val;
        dx = abs(x());
        dy = abs(y());
        dz = abs(z());
        dw = abs(w());
        val = max(dx, max(dy, max(dz,dw)));
        return val;
    }
friend int max_extend2i(const vec4i &v1,const vec4i &v2){
        int dx, dy, dz, dw, v;
        dx = (int)std::abs(float(v1.m_x - v2.m_x));
        dy = (int)std::abs(float(v1.m_y - v2.m_y));
        dz = (int)std::abs(float(v1.m_z - v2.m_z));
        dw = (int)std::abs(float(v1.m_w - v2.m_w));
        v = max(dx, max(dy, max(dz,dw)));
        return v;
    }
    int max_norm(const vec4i& v){
        int dx, dy, dz, dw;
        dx = abs(m_x - v.x());
        dy = abs(m_y - v.y());
        dz = abs(m_z - v.z());
        dw = abs(m_w - v.w());
        return max(dx,max(dy,max(dz,dw)));
    }

    int  operator [](int i) const{return m_v[i];};
    int& operator [](int i){return m_v[i];};

    operator int*() { return m_v;};
    vec4i& operator = (const vec4f &v);
    vec4i operator + (const vec4i &v) const{
        return vec4i(x()+v.x(), y()+v.y(), z()+v.z(), w()+v.w());
    }
    vec4i operator + (const int s) const{
        return vec4i(x()+s, y()+s, z()+s, w()+s);
    }
    vec4i operator - (const vec4i &v) const{
        return vec4i(x()-v.x(), y()-v.y(), z()-v.z(), w()-v.w());
    }
    vec4i operator - (const int s) const{
        return vec4i(x()-s, y()-s, z()-s, w()-s);
    }
    vec4i operator - () const {
        return vec4i(-m_x, -m_y, -m_z, -m_w);
    }
    vec4i operator * (const vec4i &v) const{
        return vec4i(x()*v.x(), y()*v.y(), z()*v.z(), w()*v.w());
    }
    vec4i operator * (const int  s) const{
        return vec4i(x()*s, y()*s, z()*s, w()*s);
    }
    vec4i operator / (const vec4i &v) const{
        return vec4i(x()/v.x(), y()/v.y(), z()/v.z(), w()/v.w());
    }
    vec4i operator / (const int  s) const{
        return vec4i(x()/s, y()/s, z()/s, w()/s);
    }
    bool  operator == (const vec4i &v)const{
        return (x()==v.x() && y()==v.y() && z()==v.z() && w()==v.w());
    }
    bool  operator != (const vec4i &v)const{
        return !(*this == v);
    }
    vec4i& operator += (const vec4i &v){
        m_x += v.x();
        m_y += v.y();
        m_z += v.z();
        m_w += v.w();
        return *this;
    }
    vec4i& operator += (int s){
        m_x += s;
        m_y += s;
        m_z += s;
        m_w += s;
        return *this;
    }
    vec4i& operator -= (const vec4i &v){
        m_x -= v.x();
        m_y -= v.y();
        m_z -= v.z();
        m_w -= v.w();
        return *this;
    }
    vec4i& operator -= (int s){
        m_x -= s;
        m_y -= s;
        m_z -= s;
        m_w -= s;
        return *this;
    }
    vec4i& operator *= (const vec4i &v){
        m_x *= v.x();
        m_y *= v.y();
        m_z *= v.z();
        m_w *= v.w();
        return *this;
    }
    vec4i& operator *= (const int s){
        m_x *= s;
        m_y *= s;
        m_z *= s;
        m_w *= s;
        return *this;
    }
    vec4i& operator /= (const vec4i &v){
        m_x /= v.x();
        m_y /= v.y();
        m_z /= v.z();
        m_w /= v.w();
        return *this;
    }
    vec4i& operator /= (const int s){
        m_x /= s;
        m_y /= s;
        m_z /= s;
        m_w /= s;
        return *this;
    }
    //lexicographical order.
    bool operator < (const vec4i& v) const{
        if (m_x < v.m_x) return true;
        else if (m_x > v.m_x) return false;
        else if (m_y < v.m_y) return true;
        else if (m_y > v.m_y) return false;
        else if (m_z < v.m_z) return true;
        else if (m_z > v.m_z) return false;
        else return (m_w < v.m_w);
    }
    bool operator > (const vec4i& v) const{
        if (m_x > v.m_x) return true;
        else if (m_x < v.m_x) return false;
        else if (m_y > v.m_y) return true;
        else if (m_y < v.m_y) return false;
        else if (m_z > v.m_z) return true;
        else if (m_z < v.m_z) return false;
        else return (m_w > v.m_w);
    }

    friend vec4i operator * (const int s, const vec4i &v){
        return v*s;
    }
    friend ostream& operator << (ostream& os, const vec4i& v)
    {
           os<<"("<<v.x()<<", "<<v.y()<<", "<<v.z()<<", "<<v.w()<<")\n";
           return os;
    };

};//end of vec4i
};//end of namespace math
#endif

