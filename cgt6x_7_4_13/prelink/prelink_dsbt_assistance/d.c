
#include <stdio.h>

__declspec(dllexport) int func_d();

__declspec(dllimport) int printf(const char *format, ...);

int func_d()
{
   printf("func_d returns 0xd\n");
   return ((int)(0xd));
}
