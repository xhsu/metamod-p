export module hlsdk:engine;

#ifdef EXPORT
#undef EXPORT
#endif

#ifdef INCLUDED_IN_MODULE
#undef INCLUDED_IN_MODULE
#endif

#define EXPORT export
#define INCLUDED_IN_MODULE

extern "C++"
{
#include "hlsdk.engine.hpp"
}
