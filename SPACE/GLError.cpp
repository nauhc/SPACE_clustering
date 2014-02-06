#include "GLError.h"
#include "GL/glew.h"
#include <QMessageBox>
#include <QDebug>

namespace lily{
#define MAX_ERROR_LENGTH 256

GLError::GLError(void)
{
}

GLError::~GLError(void)
{
}

void GLError::glCheckError(const char* call)
{
	char enums[][20] =
	{
		"invalid enumeration", // GL_INVALID_ENUM
		"invalid value",       // GL_INVALID_VALUE
		"invalid operation",   // GL_INVALID_OPERATION
		"stack overflow",      // GL_STACK_OVERFLOW
		"stack underflow",     // GL_STACK_UNDERFLOW
		"out of memory"        // GL_OUT_OF_MEMORY
	};

	GLenum errcode = glGetError();
	if (errcode == GL_NO_ERROR)
		return;

	errcode -= GL_INVALID_ENUM;
	QString message;
	message.sprintf("OpenGL %s in '%s'",enums[errcode], call);
	//qWarning()<<message;
    ErrorMessage(message);
}

void GLError::purgePreviousGLError()
{
    glGetError();
}

void GLError::ErrorMessage( const QString &msg )
{
	QMessageBox::warning(NULL,"Error",msg,QMessageBox::Ok);
	exit(1);
}

void GLError::WarningMessage( const QString &msg,QWidget* parent )
{
	qDebug()<<msg;
	QMessageBox::warning(parent,"Warning",msg,
		QMessageBox::Ok, QMessageBox::NoButton);
}

}//end of namespace