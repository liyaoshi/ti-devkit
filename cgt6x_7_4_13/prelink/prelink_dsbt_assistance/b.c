
#include <stdio.h>

__declspec(dllexport) int func_b();
__declspec(dllexport) unsigned long get_bs_funca_address();

__declspec(dllimport) int func_a();
__declspec(dllimport) int func_d();

__declspec(dllimport) int printf(const char *_format, ...);

int func_b()
{
   int b_val = (0xb << 12); 
   
   b_val |= func_a();
   b_val <<= 4;
   b_val |= func_d(); 
   
   return b_val;
}

unsigned long get_bs_funca_address()
{
   return ((unsigned long)&func_a);
}

