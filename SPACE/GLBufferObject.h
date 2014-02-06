#ifndef _GLBUFFEROBJECT_H_
#define _GLBUFFEROBJECT_H_

#pragma once
#include <GL/glew.h>

namespace lily{

class GLBufferObject
{
public:
    //Provide a Base class for generating/deleting OpenGL buffer object
    //using glGenBuffers()/glDeleteBuffers()
    //target:
    // GL_ARRAY_BUFFER_ARB:VBO with glEnableClientState(GL_VERTEX_ARRAY);
    // GL_ELEMENT_ARRAY_BUFFER_ARB:VBO+IndexBO with glDrawElements();
    // GL_PIXEL_PACK_BUFFER_ARB,GL_PIXEL_UNPACK_BUFFER_ARB: Pixel Buffer Object
    //usage:
    // GL_STATIC_DRAW_ARB,GL_STATIC_READ_ARB,GL_STATIC_COPY_ARB
    // GL_DYNAMIC_DRAW_ARB,GL_DYNAMIC_READ_ARB,GL_DYNAMIC_COPY_ARB
    // GL_STREAM_DRAW_ARB,GL_STREAM_READ_ARB,GL_STREAM_COPY_ARB
    GLBufferObject(GLenum target, GLenum usage);
    virtual ~GLBufferObject(void);
    size_t getSizeInBytes() const { return m_size;}
    GLuint getId()   const { return m_id;}
    void   deleteBuffer();
    void   bind();
    void   unbind();
    //************************************
    // Returns:   void*: returned pointer to PBO buffer that can be man    // ipulated by CPU client.
    // Parameter: GLenum usage: hint for usage:GL_READ_WRITE(default), GL_READ_ONLY_ARB
    //************************************
    void*  map(GLenum usage=GL_READ_WRITE);
    bool   unmap();
    //************************************
    // Returns: void*: The device pointer that points to the mapped PBO
    // buffer in CUDA address space.
    // Description: Get the address of mapped PBO buffer in CUDA address space.
    // Parameter: size_t * numBytes: The size in bytes of the mapped buffer object.
    //************************************
    void* getCudaMappedPointer();
    //************************************
    // Description: User must call this function to release cuda resource,
    // once they have finish using mapped cuda pointer.
    //************************************
    void  unmapCudaPointer();

protected:
    size_t m_size;//size of the buffer in bytes.
    GLenum m_target;
    GLenum m_usage;//GL_STATIC_DRAW_ARB,GL_STATIC_READ_ARB,GL_STATIC_COPY_ARB
                   //GL_DYNAMIC_DRAW_ARB,GL_DYNAMIC_READ_ARB,GL_DYNAMIC_COPY_ARB
                   //GL_STREAM_DRAW_ARB,GL_STREAM_READ_ARB,GL_STREAM_COPY_ARB
    GLuint m_id;

};
}//end of namespace
#endif