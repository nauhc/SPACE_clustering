#ifndef _GL_CONFIG_H_
#define  _GL_CONFIG_H_
#pragma once

namespace lily{

#ifdef WIN32
#define __func__ __FUNCTION__
#else
#ifdef __APPLE__
#endif
#endif
}
#endif