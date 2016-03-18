
__declspec(dllexport) int func_c();

__declspec(dllimport) int myprintf(const char *_format, ...);

int func_c()
{
   myprintf("func_c returns 0xc\n");
   return ((int)(0xc));
}

