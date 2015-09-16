#include "Object.h"

unsigned short Object::nHeapObjects = 0;
Object* Object::heapObject[USHRT_MAX];
