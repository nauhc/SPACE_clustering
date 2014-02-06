//AUTHOR: Jinrong Xie (stonexjr@gmail.com)
//CREATED: 2013-10-23
//UPDATED: 2014-01-08
// 
#ifndef _GLVERTEXBUFFEROBJECT_H_
#define _GLVERTEXBUFFEROBJECT_H_
#pragma once
#include <GLBufferObject.h>
#include <GLAttribute.h>
#include <GLError.h>
#include <vector>
#include <map>
#include <string>
//Might think about using latest GLSL API since 4.0 like, glBindVertexBuffer,
//glVertexAttribFormat,glVertexAttribBinding
namespace lily{

template<typename T>
class GLVertexBufferObject :
    public GLBufferObject
{
public:
    
    //The vertex/color/normal/texture array are organized into an array of
    //structure(interleaved array). The boundary is specified by the vertex/color/normal/texture
    // offset and stride. http://www.opengl.org/wiki/Client-Side_Vertex_Arrays
    //Vertex attribute data will not be upload to GPU until the invocation of bind().
    //which call upload() to transfer data.
    //GLenum geotype:
    //Specifies what kind of primitives are constructed
    //and how the array elements construct those primitives.
    //It could be GL_TRIANGLES, GL_POLYGON, GL_QUAD, etc.
    //GLenum usage: 
    //How user will be reading/writing from/to the buffer,
    // and how often the user will be changing it relative to the use of data.
    //GL_STATIC_DRAW, GL_STATIC_READ,
    //GL_STATIC_COPY, GL_DYNAMIC_DRAW,
    //GL_DYNAMIC_READ, GL_DYNAMIC_COPY
    //GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY
    GLVertexBufferObject(GLenum geotype, GLenum usage=GL_STATIC_DRAW, bool warning=false);

    ~GLVertexBufferObject(void);


    void enableVertex(bool flag){ m_hasVertex = flag;}
    void enableNormal(bool flag){ m_hasNormal = flag;}
    void enableColor(bool flag){ m_hasColor = flag;}
    void enableTexture(bool flag, GLenum texUnitId=0){ m_hasTextures[texUnitId] = flag;}

    void setVertexType(GLenum type=GL_FLOAT){ m_vertexType = type;}
    void setColorType(GLenum type=GL_FLOAT){ m_colorType = type;}
    void setNormalType(GLenum type=GL_FLOAT){ m_normalType = type;}
    void setTextureType(GLenum type=GL_FLOAT,GLenum texUnitId=0);//{ m_textureType = type;}

    void setVertexComponetSize(GLuint s){ m_vertexComponetCount = s;}
    void setColorComponentSize(GLuint s){ m_colorComponentCount = s;}
    //texUnitId: GL_TEXTURE0, GL_TEXTURE1,...GL_TEXTURE031
    void setTextureComponentSize(GLuint s, GLenum texUnitId=0);
    //The stride parameter defines the amount of bytes required 
    //to get from one vertex to the next,
    void setVertexStrideInBytes(GLuint s){ m_vertexStrideInBytes = s;}
    void setNormalStrideInBytes(GLuint s){ m_normalStrideInBytes = s;}
    void setColorStrideInBytes(GLuint s){ m_colorStrideInBytes = s;}
    //texUnitId: 0<==>GL_TEXTURE0, 1<==>GL_TEXTURE1,...31 <==> GL_TEXTURE31
    void setTextureStrideInBytes(GLuint s, GLenum texUnitId=0);//{ 

    //If you use GLVertexBufferObject as VBO, s is the offset into a 
    //currently bound buffer object. If you use it as Vertex Array.
    //the offset should be the pointer to the client data buffer.
    void setVertexOffsetInBytes(GLuint s){ m_vertexOffsetInBytes = s; }
    void setNormalOffsetInBytes(GLuint s){ m_normalOffsetInBytes = s;}
    void setColorOffsetInBytes(GLuint s){ m_colorOffsetInBytes = s;}
    //texUnitId: 0<==>GL_TEXTURE0, 1<==>GL_TEXTURE1,...31 <==> GL_TEXTURE31
    void setTextureOffsetInBytes(GLuint s, GLenum texUnitId=0);//{}

	bool getEnableWarning() const { return m_enableWarning; }
	void setEnableWarning(bool val) { m_enableWarning = val; }
    //Add additional user defined attribute for the vertex. 
    //Note:
    //On one hand, in lower GLSL version like 1.1 or compatibility mode of higher GLSL.
    //User can specified customized vertex attribute using the keyword
    //"attribute" in GLSL shader. addAttribute() is used to specified
    //the layout(component size, byte size, byte offset) of the corresponding
    //attribute in the currently binded GLVertexBufferObject.
    //Please refer to sample code: GLExtensionTutorial3-VBO-IBO-Attribute-Shader
    //
    //On the other hand, the core mode of GLSL 4.0 or higher requires that standard vertex 
    //attribute such as position, color, normal and texture be treated as 
    //"in" attribute in shader. And the keyword "attribute", default gl_ModelViewProjectionMatrix
    //etc. are deprecated(even no longer available) in the shader.
    //Therefore, addAttribute can also be used to specify standard vertex
    //attributes.
    //Please refer to sample code: GLExtensionTutorial4-VBO-IBO-Attribute-Shader4_3
    void addAttribute(GLuint shaderProgId, const std::string& name,GLenum type=GL_FLOAT,
                   GLuint size=3, GLuint stride=0, GLuint offset=0, bool normalized=0);

    GLAttribute* getAttribute(const std::string& name);
	//Return the id of the associated shader program if set, since GLVertexBufferObject
	//can work w/o shader. Can only be set via AddAttribute().
	GLint getShaderProgId() const { return m_shaderProgId; }
	void   setShaderProgId(GLuint progId);
    void clear();
    //bind current VBO and enable client states(vertex/color/normal/texture)
    void bind();
    //unbind current VBO and disable client states(vertex/color/normal/texture)
    void unbind();

    //Reserve required device memory and then upload vertex attributes to GPU.
    void upload();
    //When draw() is called, it uses count sequential elements from each
    //enabled array to construct a sequence of geometric primitives,beginning 
    //with element first. Or you can treat count as the number of vertices
    //involved in the draw().
    void draw(GLuint first=0, GLuint count=0);

    GLVertexBufferObject& operator << (const T v);

	const std::vector<T>& getDataBuffer() const { return m_dataBuffer; }
	void setDataBuffer(const std::vector<T>& val) { m_dataBuffer = val; }
private:
    //http://www.opengl.org/wiki/Vertex_Formats
    //http://www.opengl.org/wiki/Client-Side_Vertex_Arrays
    void enableGLClientState();
    void disableGLClientState();

    GLenum m_geotype;

    bool m_hasVertex;
    bool m_hasNormal;
    bool m_hasColor;
    bool m_hasTextures[32];
    int  m_TextureCount;//number of active textures.

    GLenum m_vertexType;
    GLenum m_colorType;
    GLenum m_normalType;
    GLenum m_textureType[32];

    GLuint m_vertexComponetCount;
    GLuint m_colorComponentCount;
    GLuint m_textureComponentCount[32];

    GLuint m_vertexStrideInBytes;
    GLuint m_normalStrideInBytes;
    GLuint m_colorStrideInBytes;
    GLuint m_textureStride[32];

    GLuint m_vertexOffsetInBytes;
    GLuint m_normalOffsetInBytes;
    GLuint m_colorOffsetInBytes;
    GLuint m_textureOffset[32];

    //vertex attributes:position,color,normal, texture, and user defined attributes
    //can be feed into this buffer before upload to server side.
    std::vector<T> m_dataBuffer;
	GLsizeiptr	   m_dataBufferSizeInBytes;
    std::map<string, GLAttribute*> m_attribs;
    GLsizeiptr     m_attribsSizeInBytes;
	//The id of the associated shader program if set. Can merely be set via AddAttribute().
	GLint	m_shaderProgId;
	bool    m_enableWarning;
	
public:
    std::map<GLenum, GLuint> g_GLTypeSizeInBytes;
};

template<typename T>
void lily::GLVertexBufferObject<T>::setShaderProgId( GLuint progId )
{
	for (std::map<string, GLAttribute*>::iterator it = m_attribs.begin();
		it != m_attribs.end() ; ++it)
	{
		//check if the current attribute is active.
		it->second->setShaderProgId(progId);
	}
}

template<typename T>
GLVertexBufferObject<T>::GLVertexBufferObject(GLenum geotype, GLenum usage/*GL_STATIC_DRAW*/, bool warning/*=false*/)
    :GLBufferObject(GL_ARRAY_BUFFER, usage),m_geotype(geotype),
    m_hasVertex(false), m_hasColor(false), m_hasNormal(false), 
    m_vertexComponetCount(3),m_vertexType(0), m_vertexStrideInBytes(3), m_vertexOffsetInBytes(0),
    m_colorComponentCount(3),m_colorType(0),  m_colorStrideInBytes(0), m_colorOffsetInBytes(0),
    m_normalStrideInBytes(0),m_normalType(0), m_normalOffsetInBytes(0),m_dataBufferSizeInBytes(0),
    m_attribsSizeInBytes(0), m_enableWarning(warning)
{

    memset(m_hasTextures,   0, sizeof(m_hasTextures));
    memset(m_textureType,   0, sizeof(m_textureType));
    memset(m_textureStride, 0, sizeof(m_textureStride));
    memset(m_textureOffset, 0, sizeof(m_textureOffset));
    memset(m_textureComponentCount,   0, sizeof(m_textureComponentCount));

    g_GLTypeSizeInBytes[GL_FLOAT]			= sizeof(GLfloat);
    g_GLTypeSizeInBytes[GL_DOUBLE]			= sizeof(GLdouble);
    g_GLTypeSizeInBytes[GL_INT]				= sizeof(GLint);
    g_GLTypeSizeInBytes[GL_UNSIGNED_BYTE]	= sizeof(GLubyte);
    g_GLTypeSizeInBytes[GL_UNSIGNED_INT]	= sizeof(GLuint);
    //....
}

template<typename T>
GLVertexBufferObject<T>::~GLVertexBufferObject(void)
{
    clear();
    unbind();
}

template<typename T>
void GLVertexBufferObject<T>::clear()
{
    m_dataBuffer.clear();
    m_dataBufferSizeInBytes = 0;

}
template<typename T>
void GLVertexBufferObject<T>::bind()
{
    GLBufferObject::bind();
    GLError::glCheckError(__func__);
    enableGLClientState();
    upload();
    GLError::glCheckError(__func__);
}
template<typename T>
void GLVertexBufferObject<T>::unbind()
{
    disableGLClientState();
    GLBufferObject::unbind();
}
template<typename T>
void GLVertexBufferObject<T>::enableGLClientState()
{
    //gl[Vertex/Color/Normal/Texture]Pointer() is supported since GL 1.1
    //Same functionality can be achieved using glVertexAttribFormat
    if (m_hasVertex)
    {
        if (m_vertexType==0)
        {
            GLError::ErrorMessage(__func__":Please set vertex type!\n");
        }
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(m_vertexComponetCount, m_vertexType/*GL_FLOAT*/, m_vertexStrideInBytes, 
            reinterpret_cast<const GLvoid*>(m_vertexOffsetInBytes));
        GLError::glCheckError(__func__);
    }
    if (m_hasColor)
    {
        if (m_colorType==0)
        {
            GLError::ErrorMessage(__func__":Please set color type!\n");
        }
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(m_colorComponentCount, m_colorType /*GL_FLOAT*/, m_colorStrideInBytes, 
            reinterpret_cast<const GLvoid*>(m_colorOffsetInBytes));
        GLError::glCheckError(__func__);
    }
    if (m_hasNormal)
    {
        if (m_normalType==0)
        {
            GLError::ErrorMessage(__func__":Please set normal type!\n");
        }
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(                      m_normalType /*GL_FLOAT*/, m_normalStrideInBytes,
            reinterpret_cast<const GLvoid*>(m_normalOffsetInBytes));
        GLError::glCheckError(__func__);
    }

    for (int i = 0 ; i < 32 ; i++)
    {
        if (m_hasTextures[i])
        {
            if (m_textureType[i]==0)
            {
                GLError::ErrorMessage(__func__":Please set texture type!\n");
            }
            glClientActiveTexture(GL_TEXTURE0+i);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(m_textureComponentCount[i], m_textureType[i]/*GL_FLOAT*/, m_textureStride[i],
                reinterpret_cast<const GLvoid*>(m_textureOffset[i]));
            GLError::glCheckError(__func__);
        }
    }
	/*
    //bind user defined attributes.
	//https://www.opengl.org/sdk/docs/man/xhtml/glGetActiveAttrib.xml
	if (getShaderProgId() > 0)
	{
		int index=0;
		#define maxLength 255
		GLenum  type=0;
		GLchar  name[maxLength]={0};
		GLint nActiveAttrib=0;
		glGetProgramiv(getShaderProgId(), GL_ACTIVE_ATTRIBUTES, &nActiveAttrib);	
		for (int index = 0 ; index < nActiveAttrib ; index++)
		{//Only bind active attribute.
			GLsizei length=-1;
			GLint	size=-1;
			glGetActiveAttrib(getShaderProgId(), index, 
						maxLength-1, &length, &size, &type, name);
			name[length]='\0';
			string strName(name);
			if ( m_attribs.find(strName)==m_attribs.end())
			{
				if (m_enableWarning)
				{
					char msg[1024];
					sprintf(msg,__func__": Attribute %s is not added in the GLVertexBufferObject.\n",name);
					//GLError::WarningMessage(msg);
					cout << msg;
				}
			}else{
				m_attribs[strName]->bind();
			}
		}
	}
	*/
    for (std::map<string, GLAttribute*>::iterator it = m_attribs.begin();
        it != m_attribs.end() ; ++it)
    {
		//check if the current attribute is active.
        it->second->bind();
    }
    GLError::glCheckError(__func__);
}
template<typename T>
void GLVertexBufferObject<T>::disableGLClientState()
{
	GLError::glCheckError(__func__"0");
    if (m_hasVertex)
    {
        glDisableClientState(GL_VERTEX_ARRAY);
    }
	GLError::glCheckError(__func__"1");
    if (m_hasColor)
    {
        glDisableClientState(GL_COLOR_ARRAY);
    }
    if (m_hasNormal)
    {
        glDisableClientState(GL_NORMAL_ARRAY);
    }
	GLError::glCheckError(__func__"3");
    for (int i = 0 ; i < 32 ; i++)
    {
        if (m_hasTextures[i])
        {
            glClientActiveTexture(GL_TEXTURE0+i);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
    }
    //unbind user defined attributes.
    for (std::map<string, GLAttribute*>::iterator it = m_attribs.begin();
        it != m_attribs.end() ; ++it)
    {
        it->second->unbind();
    }
    GLError::glCheckError(__func__"4");
}

template<typename T>
GLVertexBufferObject<T>& GLVertexBufferObject<T>::operator<<( const T v )
{
    m_dataBuffer.push_back(v);
    return *this;
}

template<typename T>
void GLVertexBufferObject<T>::upload()
{
    if (!m_dataBuffer.empty())
    {//CPU data only upload once.
        m_dataBufferSizeInBytes = m_dataBuffer.size()*sizeof(T);
        glBufferData(m_target, m_dataBufferSizeInBytes, m_dataBuffer.data(), m_usage);
        m_dataBuffer.clear();//data uploaded to GPU, no need to keep the CPU counter part.
    }
    GLError::glCheckError(__func__);
}
template<typename T>
void GLVertexBufferObject<T>::draw(GLuint first/*=0*/, GLuint count/*=0*/)
{
    //count how many floats the attributes of a vertex take up.
    if (m_hasVertex && g_GLTypeSizeInBytes.find(m_vertexType)==g_GLTypeSizeInBytes.end())
    {
        GLError::ErrorMessage(__func__": cannot recognize the m_vertexType\n");
    }
    if (m_hasColor && g_GLTypeSizeInBytes.find(m_colorType)==g_GLTypeSizeInBytes.end())
    {
        GLError::ErrorMessage(__func__": cannot recognize the m_colorType\n");
    }
    if (m_hasNormal && g_GLTypeSizeInBytes.find(m_normalType)==g_GLTypeSizeInBytes.end())
    {
        GLError::ErrorMessage(__func__": cannot recognize the m_normalType\n");
    }
    int bytesPerVertex  =(m_hasVertex  ? m_vertexComponetCount * g_GLTypeSizeInBytes[m_vertexType] : 0);
    bytesPerVertex +=(m_hasColor   ? m_colorComponentCount * g_GLTypeSizeInBytes[m_colorType] : 0);
    bytesPerVertex +=(m_hasNormal  ? 3 * g_GLTypeSizeInBytes[m_normalType] : 0);

    for (int i = 0 ; i < 32 ; i++)
    {
        if (m_hasTextures[i] && g_GLTypeSizeInBytes.find(m_textureType[i])==g_GLTypeSizeInBytes.end())
        {
            char msg[1024];
            sprintf(msg,__func__": cannot recognize the m_textureType in texture unit %d\n",i);
            GLError::ErrorMessage(msg);
        }
        bytesPerVertex += (m_hasTextures[i] ? m_textureComponentCount[i] * g_GLTypeSizeInBytes[m_textureType[i]] : 0);
    }

    bytesPerVertex += m_attribsSizeInBytes;
    //Considering alignment. The computed bytesPerVertex of type T maybe 
    // smaller than sizeof(T). We should use the larger one.
    bytesPerVertex = bytesPerVertex < sizeof(T) ? sizeof(T) : bytesPerVertex;
    if (m_dataBufferSizeInBytes % bytesPerVertex != 0)
    {
        GLError::ErrorMessage("GLVertexBufferObject::draw() m_dataBuffer.size() in byte is not multiple of bytesPerVertex\nMake sure you feed the VBO with correct number of data.");
    }
    //if count is 0, simply draw the entire data.
    count = count > 0 ? count : (m_dataBufferSizeInBytes/bytesPerVertex);

    glDrawArrays(m_geotype, first, count);
    GLError::glCheckError(__func__);
}

template<typename T>
void GLVertexBufferObject<T>::setTextureType( GLenum type/*=GL_FLOAT*/,GLenum texUnitId/*=GL_TEXTURE0*/ )
{
    if (!m_hasTextures[texUnitId])
    {
        char msg[1024];
        sprintf(msg, __func__":Please enable GL_TEXTURE%d first by calling GLVertexBufferObject::enableTexture()",texUnitId);
        GLError::ErrorMessage(msg);
    }
    m_textureType[texUnitId] = type;
}

template<typename T>
void GLVertexBufferObject<T>::setTextureComponentSize( GLuint s,GLenum texUnitId/*=0*/ )
{
    if (!m_hasTextures[texUnitId])
    {
        char msg[1024];
        sprintf(msg, __func__":Please enable GL_TEXTURE%d first by calling GLVertexBufferObject::enableTexture()",texUnitId);
        GLError::ErrorMessage(msg);
    }
    m_textureComponentCount[texUnitId] = s;
}
template<typename T>
void GLVertexBufferObject<T>::setTextureStrideInBytes( GLuint s, GLenum texUnitId/*=0*/ )
{
    if (!m_hasTextures[texUnitId])
    {
        char msg[1024];
        sprintf(msg, __func__":Please enable GL_TEXTURE%d first by calling GLVertexBufferObject::enableTexture()",texUnitId);
        GLError::ErrorMessage(msg);
    }
    m_textureStride[texUnitId] = s;
}
template<typename T>
void GLVertexBufferObject<T>::setTextureOffsetInBytes( GLuint s, GLenum texUnitId/*=0*/ )
{
    if (!m_hasTextures[texUnitId])
    {
        char msg[1024];
        sprintf(msg, __func__":Please enable GL_TEXTURE%d first by calling GLVertexBufferObject::enableTexture()",texUnitId);
        GLError::ErrorMessage(msg);
    }
    m_textureOffset[texUnitId] = s;
}

template<typename T>
void GLVertexBufferObject<T>::addAttribute(GLuint shaderProgId, const std::string& name,GLenum type/*GL_FLOAT*/,
                                        GLuint size/*3*/, GLuint stride/*=0*/, GLuint offset/*=0*/, bool normalized/*=0*/ )
{
    if ( g_GLTypeSizeInBytes.find(type)==g_GLTypeSizeInBytes.end())
    {
        GLError::ErrorMessage(__func__": cannot recognize the attribute type\n");
    }
    if (m_attribs.find(name) == m_attribs.end())
    {//add only when not present in m_attribs.
		m_shaderProgId = shaderProgId;
        m_attribs[name] = new GLAttribute( shaderProgId, name,type,size,
								stride,offset,normalized,m_enableWarning );
        m_attribsSizeInBytes += (size * g_GLTypeSizeInBytes[type]);
    }
}

template<typename T>
GLAttribute* GLVertexBufferObject<T>::getAttribute( const std::string& name )
{
    if(m_attribs.find(name)!= m_attribs.end())
        return m_attribs[name];
    else
        return NULL;
}


}//end of namespace lily
#endif