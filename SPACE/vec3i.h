//AUTHOR: Jinrong Xie (stonexjr@gmail.com)
//CREATED: 2013-10-23
//UPDATED: 2014-01-13
#ifndef _VEC3I_H_
#define _VEC3I_H_
#pragma once
#include <cmath>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

namespace lily{
class vec3f;

class vec3i
{
private:
    union{
        struct{
            int m_x, m_y, m_z;
        };
        struct{
            int m_v[3];
        };
    };

public:
    vec3i(void):m_x(0),m_y(0),m_z(0) {};
    vec3i(int x, int y, int z):m_x(x),m_y(y),m_z(z) {};
	explicit vec3i(int s):m_x(s),m_y(s),m_z(s) {};
	explicit vec3i(const vec3f &v);
    explicit vec3i(const int vs[3]):m_x(vs[0]),m_y(vs[1]),m_z(vs[2]){};

    int x() const {return m_x;}
    int y() const {return m_y;}
    int z() const {return m_z;}
    int v(int i) const { return m_v[i];}
    void  setX(int x) {m_x = x;}
    void  setY(int y) {m_y = y;}
    void  setZ(int z) {m_z = z;}
    int max_extend1i() const{
        int dx, dy, dz, val;
        dx = abs(x());
        dy = abs(y());
        dz = abs(z());
        val = max(dx, max(dy, dz));
        return val;
    }
friend int max_extend2i(const vec3i &v1,const vec3i &v2){
        int dx, dy, dz, v;
        dx = (int)std::abs(float(v1.m_x - v2.m_x));
        dy = (int)std::abs(float(v1.m_y - v2.m_y));
        dz = (int)std::abs(float(v1.m_z - v2.m_z));
        v = max(dx, max(dy, dz));
        return v;
    }

    int min_extend1i() const{
        int dx, dy, dz, val;
        dx = abs(x());
        dy = abs(y());
        dz = abs(z());
        val = min(dx, min(dy, dz));
        return val;
    }
friend int min_extend2i(const vec3i &v1,const vec3i &v2){
        int dx, dy, dz, v;
        dx = (int)std::abs(float(v1.m_x - v2.m_x));
        dy = (int)std::abs(float(v1.m_y - v2.m_y));
        dz = (int)std::abs(float(v1.m_z - v2.m_z));
        v = min(dx, min(dy, dz));
        return v;
    }


    int max_norm(const vec3i& v){
        int dx, dy, dz;
        dx = abs(m_x - v.x());
        dy = abs(m_y - v.y());
        dz = abs(m_z - v.z());
        return max(dx,max(dy,dz));
    }

	int  operator [](int i) const{return m_v[i];};
	int& operator [](int i){return m_v[i];};

    operator int*() { return m_v;};
    vec3i& operator = (const vec3f &v);
    vec3i  operator + (const vec3i &v) const{
        return vec3i(x()+v.x(), y()+v.y(), z()+v.z());
    }
    vec3i operator + (const int s) const{
        return vec3i(x()+s, y()+s, z()+s);
    }
    vec3i operator - (const vec3i &v) const{
        return vec3i(x()-v.x(), y()-v.y(), z()-v.z());
    }
    vec3i operator - (const int s) const{
        return vec3i(x()-s, y()-s, z()-s);
    }
    vec3i operator - () const{
        return vec3i(-m_x, -m_y, -m_z);
    }
    vec3i operator * (const vec3i &v) const{
        return vec3i(x()*v.x(), y()*v.y(), z()*v.z());
    }
    vec3i operator * (const int  s) const{
        return vec3i(x()*s, y()*s, z()*s);
    }
    vec3i operator / (const vec3i &v) const{
        return vec3i(x()/v.x(), y()/v.y(), z()/v.z());
    }
    vec3i operator / (const int  s) const{
        return vec3i(x()/s, y()/s, z()/s);
    }
    bool  operator == (const vec3i &v)const{
        return (x()==v.x() && y()==v.y() && z()==v.z());
    }
    bool  operator != (const vec3i &v)const{
        return !(*this == v);
    }
    vec3i& operator += (const vec3i &v){
        m_x += v.x();
        m_y += v.y();
        m_z += v.z();
        return *this;
    }
    vec3i& operator += (int s){
        m_x += s;
        m_y += s;
        m_z += s;
        return *this;
    }
    vec3i& operator -= (const vec3i &v){
        m_x -= v.x();
        m_y -= v.y();
        m_z -= v.z();
        return *this;
    }
    vec3i& operator -= (int s){
        m_x -= s;
        m_y -= s;
        m_z -= s;
        return *this;
    }
    vec3i& operator *= (const vec3i &v){
        m_x *= v.x();
        m_y *= v.y();
        m_z *= v.z();
        return *this;
    }
    vec3i& operator *= (const int s){
        m_x *= s;
        m_y *= s;
        m_z *= s;
        return *this;
    }
    vec3i& operator /= (const vec3i &v){
        m_x /= v.x();
        m_y /= v.y();
        m_z /= v.z();
        return *this;
    }
    vec3i& operator /= (const int s){
        m_x /= s;
        m_y /= s;
        m_z /= s;
        return *this;
    }
    //lexicographical order.
    bool operator < (const vec3i& v) const{
        if (m_x < v.m_x) return true;
        else if (m_x > v.m_x) return false;
        else if (m_y < v.m_y) return true;
        else if (m_y > v.m_y) return false;
        else return (m_z < v.m_z);
    }
    bool operator > (const vec3i& v) const{
        if (m_x > v.m_x) return true;
        else if (m_x < v.m_x) return false;
        else if (m_y > v.m_y) return true;
        else if (m_y < v.m_y) return false;
        else return (m_z > v.m_z);
    }

    friend vec3i operator * (const int s, const vec3i &v){
        return v*s;
    }
	//for standard I/O and File input
	friend ostream& operator << (ostream& os, const vec3i& v)
	{
		os<<"("<<v.x()<<", "<<v.y()<<", "<<v.z()<<")\n";
		return os;
	};
	friend istream& operator >> (istream& is, vec3i& v)
	{
		is >> v[0] >> v[1] >> v[2];
		return is;
	};
	//for File Output
	friend ofstream& operator << (ofstream& os, const vec3i& v)
	{
		os<<" "<<v.x()<<" "<<v.y()<<" "<<v.z()<<"\n";
		return os;
	};
	friend string& operator << (string& str, const vec3i& v)
	{
		stringstream ss;
		ss <<"("<<v.x()<<", "<<v.y()<<", "<<v.z()<<")";
		str += ss.str();
		return str;
	};

static
vec3i index1D_to_index3D_uint64( size_t index1D,const vec3i &size3d );
static 
vec3i index1D_to_index3D(int index1D,const vec3i &size3d);
};//end of vec3i
};//end of namespace math
#endif

