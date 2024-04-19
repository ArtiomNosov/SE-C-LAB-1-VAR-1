#include "Debug.h"

void printDubug(const char* fmt, void* val)
{
	
#ifdef DEBUG
	printf(fmt, val);
#endif // DEBUG

}