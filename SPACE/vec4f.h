#ifndef _VEC4F_H_
#define _VEC4F_H_
#pragma once
#include <cmath>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

namespace lily{
    class vec4i;
    class vec3f;
    class vec4f
    {
    private:
        union{
            struct{
                float m_x, m_y, m_z, m_w;
            };
            struct{
                float m_r, m_g, m_b, m_a;
            };
            struct{
                float m_v[4];
            };
        };
    public:
        vec4f(void):m_x(0),m_y(0),m_z(0), m_w(0){};
        vec4f(float x, float y, float z, float w):m_x(x),m_y(y),m_z(z), m_w(w){};
        vec4f(const vec3f& v, float w);
        explicit vec4f(float s):m_x(s),m_y(s),m_z(s), m_w(s){};
        explicit vec4f(const vec4i& v);
        explicit vec4f(const float vs[4]):m_x(vs[0]),m_y(vs[1]),m_z(vs[2]), m_w(vs[3]){};

        float x() const {return m_x;}
        float y() const {return m_y;}
        float z() const {return m_z;}
        float w() const {return m_w;}
        float r() const {return m_r;}
        float g() const {return m_g;}
        float b() const {return m_b;}
        float a() const {return m_a;}
        float v(int i) const { return m_v[i];}
        void  setX(float x) {m_x = x;}
        void  setY(float y) {m_y = y;}
        void  setZ(float z) {m_z = z;}
        void  setW(float w) {m_w = w;}
        void  setR(float r) {m_r = r;}
        void  setG(float g) {m_g = g;}
        void  setB(float b) {m_b = b;}
        void  setA(float a) {m_a = a;}
        float lengthSquared() const {
            return (m_x*m_x+m_y*m_y+m_z*m_z+m_w*m_w);
        }
        float length() const {
            return sqrtf(lengthSquared());
        }
        float max_norm(const vec4f& v){
            float dx, dy, dz, dw;
            dx = fabsf(m_x - v.x());
            dy = fabsf(m_y - v.y());
            dz = fabsf(m_z - v.z());
            dw = fabsf(m_w - v.w());
            return max(dx,max(dy,max(dz,dw)));
        }
        void  normalize(){
            float inv = length();
            if (inv==0.0f){
                return;
            }
            inv = 1.0f/inv;
            m_x *= inv;
            m_y *= inv;
            m_z *= inv;
            m_w *= inv;
        }
        float dot(const vec4f &v) const { return x()*v.x()+y()*v.y()+z()*v.z()+w()*v.w();};
        float max_extend1f() const{
            float dx, dy, dz, dw, val;
            dx = fabsf(x());
            dy = fabsf(y());
            dz = fabsf(z());
            dw = fabsf(w());
            val = max(dx, max(dy, max(dz, dw)));
            return val;
        }
        friend  float max_extend2f(const vec4f &v1,const vec4f &v2){
            float dx, dy, dz, dw, v;
            dx = fabsf(v1.m_x - v2.m_x);
            dy = fabsf(v1.m_y - v2.m_y);
            dz = fabsf(v1.m_z - v2.m_z);
            dw = fabsf(v1.m_w - v2.m_w);
            v = max(dx, max(dy, max(dz,dw)));
            return v;
        }
        operator float*() { return m_v;};
        float  operator [](int i) const{return m_v[i];};
        float& operator [](int i){return m_v[i];};

        vec4f& operator = (const vec4i &v);
        vec4f operator + (const vec4f &v) const{
            return vec4f(x()+v.x(), y()+v.y(), z()+v.z(), w()+v.w());
        }
        vec4f operator + (const float s) const{
            return vec4f(x()+s, y()+s, z()+s, w()+s);
        }
        vec4f operator - (const vec4f &v) const{
            return vec4f(x()-v.x(), y()-v.y(), z()-v.z(), w()-v.w());
        }
        vec4f operator - (const float s) const{
            return vec4f(x()-s, y()-s, z()-s, w()-s);
        }
        vec4f operator - () const {
            return vec4f(-m_x, -m_y, -m_z, -m_w);
        }
        vec4f operator * (const vec4f &v) const{
            return vec4f(x()*v.x(), y()*v.y(), z()*v.z(), w()*v.w());
        }
        vec4f operator * (const float  s) const{
            return vec4f(x()*s, y()*s, z()*s, w()*s);
        }
        vec4f operator / (const vec4f &v) const{
            return vec4f(x()/v.x(), y()/v.y(), z()/v.z(), w()/v.w());
        }
        vec4f operator / (const float  s) const{
            return vec4f(x()/s, y()/s, z()/s, w()/s);
        }
        bool  operator == (const vec4f &v)const{
            return (x()==v.x() && y()==v.y() && z()==v.z() && w()==v.w());
        }
        bool  operator != (const vec4f &v)const{
            return !(*this == v);
        }
        vec4f& operator += (const vec4f &v){
            m_x += v.x();
            m_y += v.y();
            m_z += v.z();
            m_w += v.w();
            return *this;
        }
        vec4f& operator += (float s){
            m_x += s;
            m_y += s;
            m_z += s;
            m_w += s;
            return *this;
        }
        vec4f& operator -= (const vec4f &v){
            m_x -= v.x();
            m_y -= v.y();
            m_z -= v.z();
            m_w -= v.w();
            return *this;
        }
        vec4f& operator -= (float s){
            m_x -= s;
            m_y -= s;
            m_z -= s;
            m_w -= s;
            return *this;
        }
        vec4f& operator *= (const vec4f &v){
            m_x *= v.x();
            m_y *= v.y();
            m_z *= v.z();
            m_w *= v.w();
            return *this;
        }
        vec4f& operator *= (const float  s){
            m_x *= s;
            m_y *= s;
            m_z *= s;
            m_w *= s;
            return *this;
        }
        vec4f& operator /= (const vec4f &v){
            m_x /= v.x();
            m_y /= v.y();
            m_z /= v.z();
            m_w /= v.w();
            return *this;
        }
        vec4f& operator /= (const float  s){
            m_x /= s;
            m_y /= s;
            m_z /= s;
            m_w /= s;
            return *this;
        }
        //lexicographical order.
        bool operator < (const vec4f& v) const{
                 if (m_x < v.m_x) return true;
            else if (m_x > v.m_x) return false;
            else if (m_y < v.m_y) return true;
            else if (m_y > v.m_y) return false;
            else if (m_z < v.m_z) return true;
            else if (m_z > v.m_z) return false;
            else return (m_w < v.m_w);
        }
        bool operator > (const vec4f& v) const{
                 if (m_x > v.m_x) return true;
            else if (m_x < v.m_x) return false;
            else if (m_y > v.m_y) return true;
            else if (m_y < v.m_y) return false;
            else if (m_z > v.m_z) return true;
            else if (m_z < v.m_z) return false;
            else return (m_w > v.m_w);
        }
        friend vec4f operator * (const float s, const vec4f &v){
            return v*s;
        }
        //for standard I/O and File input
        friend ostream& operator << (ostream& os, const vec4f& v)
        {
            os<<"("<<v.x()<<", "<<v.y()<<", "<<v.z()<<", "<<v.w()<<")\n";
            return os;
        };
        friend istream& operator >> (istream& is, vec4f& v)
        {
            is >> v[0] >> v[1] >> v[2] >> v[3];
            return is;
        };
        //for File Output
        friend ofstream& operator << (ofstream& os, const vec4f& v)
        {
            os<<" "<<v.x()<<" "<<v.y()<<" "<<v.z()<<" "<<v.w()<<"\n";
            return os;
        };
        friend string& operator << (string& str, const vec4f& v)
        {
            stringstream ss;
            ss <<"("<<v.x()<<", "<<v.y()<<", "<<v.z()<<", "<<v.w()<<")";
            str += ss.str();
            return str;
        };
    };//end vec4f
};//end math namespace

#endif

