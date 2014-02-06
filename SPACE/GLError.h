#ifndef _GL_ERROR_H_
#define  _GL_ERROR_H_
#pragma once
#include <QString>
#include <QWidget>
#include "GLConfig.h"

namespace lily{

class GLError
{
public:
	GLError(void);
	~GLError(void);
	static	void glCheckError(const char* call);
    //Clean current GL error status.
    static  void purgePreviousGLError();
	static  void ErrorMessage(const QString &msg);
	static  void WarningMessage( const QString &msg, QWidget* parent=NULL );
};

}
#endif