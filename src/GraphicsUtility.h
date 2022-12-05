#ifndef _GraphicsUtility
#define _GraphicsUtility

#include "Enum.h"

#define ReleaseAndDeleteCOMobject(x) { if(x){ x->Release(); x = 0; } }
#define VasA(v) { &v[x] }

#endif