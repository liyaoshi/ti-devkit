
#include <stdio.h>

__declspec(dllexport) int func_c();

__declspec(dllimport) int printf(const char *_format, ...);

int func_c()
{
   printf("func_c returns 0xc\n");
   return ((int)(0xc));
}

