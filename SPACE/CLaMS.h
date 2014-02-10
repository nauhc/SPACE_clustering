//AUTHOR: Jinrong Xie (stonexjr@gmail.com)
//CREATED: 2013-12-23
//UPDATED: 2014-01-13

#ifndef _CLAMS_H_
#define _CLAMS_H_
#include <cstring>
#include <GLVertexBufferObject.h>
#include <GLIndexBufferObject.h>
#include <BBox.h>
#include <vec2i.h>
#include <vec3i.h>
#include <vec4f.h>
#include <CLaMSAttribute.h>
#include "AbstractData.h"

struct vertexCLaMSAttribute 
{
    vertexPosAttribute positions;
    //float time;//time longitude and latitude.
    //float		  altitude;
    //float pressure;
    //float temperature;
    //float pot_temp;
    float pot_vorticity;
    //int   seed_id;
};

class CLaMS : public AbstractData{
public:
    CLaMS();
    ~CLaMS();
    virtual void load(const string& fileName);
    virtual void CreateVBO();
    virtual void draw();
    GLint  getCurActivePathLineId(){return m_activePathlineId;}
    void   setCurActivePathLineId(GLuint n);
    GLint  getPathLineIdMin(){ return m_pathlineIdMin;}
    GLint  getPathLineIdMax(){ return m_pathlineIdMax;}
    size_t getMaxPathlineToShow() const { return m_maxPathlineToShow; }
    void setMaxPathlineToShow(size_t val) { m_maxPathlineToShow = val; }
	void CreateVBO2();
	void draw2();
	void dumpIthPathlineTOFile();

	void clustering();

private:
   
    lily::BBox   m_bboxPlanarMode;
    lily::BBox   m_bboxSphericalMode;
    bool   m_useSphericalCoord;
    float  m_lamda;//time parameter to lerp position between planar and spherical mode.
    GLint  m_activePathlineId, m_pathlineIdMin, m_pathlineIdMax;
    size_t m_totalCount;
    size_t m_maxPathlineToShow; 
    //(start, count)Each entry indicates the start index and the count of
	//the trajectory point per pathline.
    std::vector<CLaMSAttribute> m_databuffer;
    std::vector<CLaMSPathLine>  m_pathLinesConnectivity;
    std::vector<lily::vec2i>    m_pathlineStartCountPairs;
    std::shared_ptr<GLVertexBufferObject<lily::vec3f> > m_pVBOPathLine;
    std::shared_ptr<GLIndexBufferObject> m_ibo;                 

};

#endif