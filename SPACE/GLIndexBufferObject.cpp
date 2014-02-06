#include "GLIndexBufferObject.h"
#include <GLError.h>
using namespace lily;

GLIndexBufferObject::GLIndexBufferObject(GLenum geotype, GLenum usage/*=GL_STATIC_DRAW*/)
    :GLBufferObject(GL_ELEMENT_ARRAY_BUFFER, usage),
    m_type(geotype),m_indexDataSize(0),
    m_bUseRestart(false),m_restartIndex(0)
{
}


GLIndexBufferObject::~GLIndexBufferObject(void)
{
    clear();
    unbind();
    GLError::glCheckError(__func__);
}

void GLIndexBufferObject::clear()
{
    m_indexData.clear();
    m_indexDataSize = 0;
}

void GLIndexBufferObject::upload()
{
    if (!m_indexData.empty())
    {//CPU data only upload once.
        m_indexDataSize = m_indexData.size();
        glBufferData(m_target, m_indexDataSize*sizeof(GLuint), m_indexData.data(), m_usage); 
        m_indexData.clear();//data uploaded to GPU, no need to keep the CPU counter part.
    }
    GLError::glCheckError(__func__);
}

void GLIndexBufferObject::bind()
{
    GLBufferObject::bind();
    upload();
    if (m_bUseRestart)
    {
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(m_restartIndex);
    }
    GLError::glCheckError(__func__);
}

void GLIndexBufferObject::unbind()
{
    if (m_bUseRestart)
    {
        glDisable(GL_PRIMITIVE_RESTART);
    }
    GLBufferObject::unbind();
}

void GLIndexBufferObject::draw( GLuint first/*=0*/, GLuint count/*=0*/ )
{
    count = count > 0 ? count : m_indexDataSize;
    glDrawElements(m_type, count, GL_UNSIGNED_INT, 0);
}

GLIndexBufferObject& GLIndexBufferObject::operator<<( const GLuint i )
{
    m_indexData.push_back(i);
    return *this;
}
