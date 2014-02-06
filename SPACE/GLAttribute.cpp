#include "GLAttribute.h"
#include <GLError.h>

namespace lily{

GLAttribute::GLAttribute(GLuint shaderProgId,  const string& name, GLenum type/*=GL_FLOAT*/, GLuint size/*=3*/, 
     GLuint stride/*=0*/, GLuint offset/*=0*/, bool normalized/*=false*/,bool warning/*=false*/ )
     :m_shaderProgId(shaderProgId), m_name(name),m_type(type),m_size(size),
      m_stride(stride),m_offset(offset),m_normalized(normalized),m_enableWarning(warning)
{
}

GLAttribute::~GLAttribute(void)
{
}

void GLAttribute::bind()
{
    GLint index=-1;
    index = glGetAttribLocation( m_shaderProgId, m_name.data());
    if (index==-1)
    {
        char msg[1024];
        sprintf(msg,__func__": index==-1, cannot find %s\n",m_name.data());
        GLError::ErrorMessage(msg);
    }
    glEnableVertexAttribArray(index);
    if(m_type == GL_INT || m_type == GL_UNSIGNED_BYTE
       || m_type == GL_UNSIGNED_INT){
        //We need glVertexAttribIPointer( with I) to match your shader int attribute,
        //and then also GL_INT if the host is supplying data as an int array.
        //Even though http://www.opengl.org/wiki/GLAPI/glVertexAttribIPointer
        //mentioned that glVertexAttribPointer() also takes GL_INT
        //but experiment shows, at least on Nvidia TITAN graphics card,
        //glVertexAttribPointer() would convert int data to some random large number.
        //Therefore, IPointer version is supposed to just leave the data in
        //integer form and not convert it to a float.
        glVertexAttribIPointer(index, m_size, m_type,m_stride,\
                               reinterpret_cast<const GLvoid*>(m_offset));
        //glVertexAttribPointer(index, m_size, m_type, false,m_stride,
        //                      reinterpret_cast<const GLvoid*>(m_offset));
    }
	else if (m_type == GL_DOUBLE)
	{
		glVertexAttribLPointer(index, m_size, m_type,m_stride,\
							  reinterpret_cast<const GLvoid*>(m_offset));
	}
    else{
        glVertexAttribPointer(index, m_size, m_type,m_normalized,m_stride,
                              reinterpret_cast<const GLvoid*>(m_offset));
    }

}

void GLAttribute::unbind()
{
    GLint index=-1;
    index = glGetAttribLocation( m_shaderProgId, m_name.data());
	if (index==-1)
    {
		if (m_enableWarning)
		{
			char msg[1024];
			sprintf(msg,__func__": Attribute %s is not active.\n",m_name.data());
			printf("%s",msg);
		}
    }else{
		glDisableVertexAttribArray(index);
	}
}

}//end of namespace
