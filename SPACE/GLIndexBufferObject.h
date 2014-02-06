//AUTHOR: Jinrong Xie (stonexjr@gmail.com)
//CREATED: 2013-10-25
//UPDATED: 2014-01-01
#ifndef _GL_INDEXBUFFEROBJECT_H_
#define _GL_INDEXBUFFEROBJECT_H_
#pragma once
#include <vector>
#include <GLBufferObject.h>
namespace lily{

    class GLIndexBufferObject :
        public GLBufferObject
    {
        public:
            GLIndexBufferObject(GLenum geotype, GLenum usage=GL_STATIC_DRAW);
            ~GLIndexBufferObject(void);

            void upload();
            void bind();
            void unbind();
            void draw(GLuint first=0, GLuint count=0);
            void enableRestart(bool f){ m_bUseRestart = f; };
            bool isEnableRestart() { return m_bUseRestart;};
            void setRestartIndex(GLuint idx) { m_restartIndex = idx;};
			std::vector<GLuint> getIndexData() const { return m_indexData; }
			void setIndexData(const std::vector<GLuint>& val) { m_indexData = val; }
            void clear();

            GLIndexBufferObject& operator << (const GLuint i);
            GLenum m_type;//type of geometry the object represent. GL_TRIANGLES, GL_QUADS...
            bool m_bUseRestart;
            GLuint m_restartIndex;
            std::vector<GLuint> m_indexData;
			GLuint m_indexDataSize;
    };

}
#endif
