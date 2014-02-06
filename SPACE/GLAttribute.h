//AUTHOR: Jinrong Xie (stonexjr@gmail.com)
//CREATED: 2013-11-16
//UPDATED: 2014-12-13

#ifndef _GL_ATTRIBUTE_H_
#define _GL_ATTRIBUTE_H_
#pragma once
#include <string>
#include <GL/glew.h>
using namespace std;

namespace lily{
     
class GLAttribute
{
public:
    //Vertex attribute descriptor, the actual data is store in the GLVertexBuffer Object.
    //GLAttribute only tell GLVertexBufferObject where it can locate the corresponding
    //attribute data in the VBO.
    //param size: Determines the number of components per vertex allocated to the current
    //attribute and must be 1, 2, 3 or 4. 
    //param type: Indicates the type of the data. Following table map the available GL type
    //to the actual data type:
    //---------------------------------
    //| type    | physical data type  |
    //---------------------------------
    // GL_BYTE  | GLbyte
    // GL_SHORT | GLshort
    // GL_INT   | GLint
    // GL_FIXED | GLfixed
    // GL_FLOAT | GLfloat
    // GL_HALF_FLOAT | GLhalf
    // GL_DOUBLE | GLdouble
    // GL_UNSIGNED_BYTE | GLubyte
    // GL_UNSIGNED_SHORT| GLushort
    // GL_UNSIGNED_INT  | GLuint
    //
    // param stride: Amount of bytes required to get from one vertex to the next.
    // param offset: It could be the offset into a VBO where the attribute starts.
    //              or it could be the actual pointer to the attribute array on the client side.
    // param normalized: Indicate if the data will be normalized in the pipeline.
    GLAttribute(GLuint shaderProgId, const string& name, GLenum type=GL_FLOAT,
		GLuint size=3,  GLuint stride=0, GLuint offset=0, bool normalized=false,
		bool warning=false);

    ~GLAttribute(void);

    //bind the attribute to a variable named m_name in shader program specified
    //by programId. User is responsible to prepare, compile and link shader program
    //prior the usage of GLAttribute::bind().
    void bind();
    void unbind();

	GLuint getShaderProgId() const { return m_shaderProgId; }
	void   setShaderProgId( GLuint progId ) { m_shaderProgId = progId;}
private:
    string m_name;//string representation of attribute name
    GLenum m_type;//GL data type, i.e. GL_FLOAT, GL_UNSIGNED_INT.
    GLuint m_size;//# of components(e.g floats or ints) of the attribute
    GLuint m_stride;//amount of bytes required to get from one vertex to the next
    GLuint m_shaderProgId;//The shader program id where current attribute is defined.
    //If you bindGLAttribute as VBO, s is the offset into a 
    //currently bound buffer object. If you use it as Vertex Array.
    //the offset should be the pointer to the client data buffer.
    GLuint m_offset;
    bool   m_normalized;
	bool   m_enableWarning;
};
}//end of namespace 
#endif