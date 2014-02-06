#ifndef _ABSTRACT_DATA_H_
#define _ABSTRACT_DATA_H_
#include <cstring>
#include <GLVertexBufferObject.h>
#include <GLIndexBufferObject.h>
#include <BBox.h>
#include <vec4f.h>
using namespace lily;
using namespace std;

struct vec3d 
{
    union{
        struct{
            double v[3];
        };
        struct{
            double m_x,m_y,m_z;
        };
    };
    vec3d():m_x(0.0),m_y(0.0),m_z(0.0){}
    double x(){ return m_x;}
    double y(){ return m_y;}
    double z(){ return m_z;}

    friend ostream& operator << (ostream& os, const vec3d& v){
        os <<"("<<v.m_x<<", "<<v.m_y<<", "<<v.m_z<<")\n";
        return os;
    }
};


struct vertexPosAttribute 
{
    vec3f posPlanar;
    vec3f posSpherical;
};

class AbstractData{
public:
    AbstractData()
        :m_invScale(1.0f),m_color(1.0f,1.0f,1.0f,1.0f)
        ,m_programId(-1),m_pointSize(1.0f)
        ,m_useSphericalCoord(true),m_lamda(0.0f) {};

    ~AbstractData(){};
    virtual void load(const string& fileName)=0;
    virtual void CreateVBO()=0;
    virtual void draw()=0;
    void setShaderId(int id){ m_programId = id;}
    void setPointSize(float size){ m_pointSize = size;}
    float getPointSize() const { return m_pointSize;}
    void setProjectionMode(bool mode=false){m_useSphericalCoord=mode; }
    void forwardTime(float deta_t=0.03f){m_lamda+=deta_t; m_lamda = m_lamda>1.0f? 1.0f : m_lamda;}
    void setTime(float t){m_lamda = t;}
    float getTime() const {return m_lamda;}

protected:
    int  m_programId;
    float m_invScale;
    vec4f m_color;
    float m_pointSize;
    string m_fileName;
    BBox   m_bboxPlanarMode;
    BBox   m_bboxSphericalMode;
    bool   m_useSphericalCoord;
    float  m_lamda;//time parameter to lerp position between planar and spherical mode.
    //GLIndexBufferObject *m_pIBO;
};

#endif