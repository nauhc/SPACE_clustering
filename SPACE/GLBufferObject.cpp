#include "GLBufferObject.h"
#include "GLError.h"

namespace lily{

GLBufferObject::GLBufferObject(GLenum target, GLenum usage)
    :m_target(target),m_usage(usage)
{
    glGenBuffers(1, &m_id);
}

GLBufferObject::~GLBufferObject(void)
{
    unbind();
    deleteBuffer();
    GLError::glCheckError(__func__);
}

void GLBufferObject::bind()
{
    glBindBuffer(m_target, m_id);
}

void GLBufferObject::unbind()
{
    glBindBuffer(m_target, 0);
}

void GLBufferObject::deleteBuffer()
{
    if (m_id)
    {
        glDeleteBuffers(1, &m_id);
        m_id = 0;
    }
}

bool GLBufferObject::unmap()
{
    return glUnmapBuffer(m_target);
}

void* GLBufferObject::map(GLenum usage)
{
    GLError::purgePreviousGLError();
    void* buffer = glMapBuffer(m_target,usage);
    GLError::glCheckError(__func__"()");
    return buffer;
}
}//end of namespace