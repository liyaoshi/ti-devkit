
#include <stdio.h>

__declspec(dllexport) int func_a();

__declspec(dllimport) int func_c();
__declspec(dllimport) int func_d();

__declspec(dllimport) int printf(const char *_format, ...);

int func_a()
{
   int a_val = (0xa << 4); 
   
   a_val |= func_c();
   a_val <<= 4;
   a_val |= func_d(); 
   
   return a_val;
}
