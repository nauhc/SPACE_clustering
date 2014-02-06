//AUTHOR: Jinrong Xie (stonexjr@gmail.com)
//CREATED: 2013-10-23
//UPDATED: 2014-01-13

#ifndef _VEC2I_H_
#define _VEC2I_H_
#pragma once
#include <cmath>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

namespace lily{
class vec2f;

class vec2i
{
private:
    union{
        struct{
            int m_x, m_y;
        };
        struct{
            int m_v[2];
        };
    };

public:
    vec2i(void):m_x(0),m_y(0) {};
    vec2i(int x, int y):m_x(x),m_y(y) {};
    explicit vec2i(int s):m_x(s),m_y(s) {};
    explicit vec2i(const vec2f &v);
    explicit vec2i(const int vs[2]):m_x(vs[0]),m_y(vs[1]){};

    int x() const {return m_x;}
    int y() const {return m_y;}
    int v(int i) const { return m_v[i];}
    void  setX(int x) {m_x = x;}
    void  setY(int y) {m_y = y;}

    int max_extend1i() const{
        int dx, dy, val;
        dx = abs(x());
        dy = abs(y());
        val = max(dx, dy);
        return val;
    }
friend int max_extend2i(const vec2i &v1,const vec2i &v2){
        int dx, dy, v;
        dx = (int)std::abs(float(v1.m_x - v2.m_x));
        dy = (int)std::abs(float(v1.m_y - v2.m_y));
        v = max(dx, dy);
        return v;
    }

    int min_extend1i() const{
        int dx, dy, val;
        dx = abs(x());
        dy = abs(y());
        val = min(dx, dy);
        return val;
    }
friend int min_extend2i(const vec2i &v1,const vec2i &v2){
        int dx, dy, v;
        dx = (int)std::abs(float(v1.m_x - v2.m_x));
        dy = (int)std::abs(float(v1.m_y - v2.m_y));
        v = min(dx, dy);
        return v;
    }


    int max_norm(const vec2i& v){
        int dx, dy;
        dx = abs(m_x - v.x());
        dy = abs(m_y - v.y());
        return max(dx, dy);
    }

    int  operator [](int i) const { return m_v[i];};
    int& operator [](int i) { return m_v[i];};

    operator int*() { return m_v;};
    vec2i& operator = (const vec2f &v);
    vec2i operator + (const vec2i &v) const{
        return vec2i(x()+v.x(), y()+v.y());
    }
    vec2i operator + (const int s) const{
        return vec2i(x()+s, y()+s);
    }
    vec2i operator - (const vec2i &v) const{
        return vec2i(x()-v.x(), y()-v.y());
    }
    vec2i operator - (const int s) const{
        return vec2i(x()-s, y()-s);
    }
    vec2i operator - () const {
        return vec2i(-m_x, -m_y);
    }
    vec2i operator * (const vec2i &v) const{
        return vec2i(x()*v.x(), y()*v.y());
    }
    vec2i operator * (const int  s) const{
        return vec2i(x()*s, y()*s);
    }
    vec2i operator / (const vec2i &v) const{
        return vec2i(x()/v.x(), y()/v.y());
    }
    vec2i operator / (const int  s) const{
        return vec2i(x()/s, y()/s);
    }
    bool  operator == (const vec2i &v)const{
        return (x()==v.x() && y()==v.y());
    }
    bool  operator != (const vec2i &v)const{
        return !(*this == v);
    }
    vec2i& operator += (const vec2i &v){
        m_x += v.x();
        m_y += v.y();
        return *this;
    }
    vec2i& operator += (int s){
        m_x += s;
        m_y += s;
        return *this;
    }
    vec2i& operator -= (const vec2i &v){
        m_x -= v.x();
        m_y -= v.y();
        return *this;
    }
    vec2i& operator -= (int s){
        m_x -= s;
        m_y -= s;
        return *this;
    }
    vec2i& operator *= (const vec2i &v){
        m_x *= v.x();
        m_y *= v.y();
        return *this;
    }
    vec2i& operator *= (const int s){
        m_x *= s;
        m_y *= s;
        return *this;
    }
    vec2i& operator /= (const vec2i &v){
        m_x /= v.x();
        m_y /= v.y();
        return *this;
    }
    vec2i& operator /= (const int s){
        m_x /= s;
        m_y /= s;
        return *this;
    }
    //lexicographical order.
    bool operator < (const vec2i& v) const{
        if (m_x < v.m_x) return true;
        else if (m_x > v.m_x) return false;
        else  return (m_y < v.m_y);
    }
    bool operator > (const vec2i& v) const{
        if (m_x > v.m_x) return true;
        else if (m_x < v.m_x) return false;
        else  return (m_y > v.m_y);
    }

    friend vec2i operator * (const int s, const vec2i &v){
        return v*s;
    }
    //for standard I/O and File input
    friend ostream& operator << (ostream& os, const vec2i& v)
    {
        os<<"("<<v.x()<<", "<<v.y()<<")\n";
        return os;
    };
    friend istream& operator >> (istream& is, vec2i& v)
    {
        is >> v[0] >> v[1];
        return is;
    };
    //for File Output
    friend ofstream& operator << (ofstream& os, const vec2i& v)
    {
        os<<" "<<v.x()<<" "<<v.y()<<"\n";
        return os;
    };
    friend string& operator << (string& str, const vec2i& v)
    {
        stringstream ss;
        ss <<"("<<v.x()<<", "<<v.y()<<")";
        str += ss.str();
        return str;
    };
static
vec2i index1D_to_index2D_uint64( size_t index1D,const vec2i &size2d );
static 
vec2i index1D_to_index2D(int index1D,const vec2i &size2d);
};//end of vec3i
};//end of namespace math
#endif

