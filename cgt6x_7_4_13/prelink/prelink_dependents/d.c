
__declspec(dllexport) int func_d();

__declspec(dllimport) int myprintf(const char *format, ...);

int func_d()
{
   myprintf("func_d returns 0xd\n");
   return ((int)(0xd));
}
