
__declspec(dllexport) int run_test();

__declspec(dllimport) int func_a();
__declspec(dllimport) int func_b();
__declspec(dllimport) unsigned long get_bs_funca_address();

__declspec(dllimport) int myprintf(const char *_format, ...);


int run_test()
{
   int a_counter = 0;
   unsigned long my_funca_addr = (unsigned long)&func_a;
   int b_counter = 0;
   unsigned long yo_funca_addr = get_bs_funca_address(); 
   
   myprintf("Begin Dependent Loading Test ... "); 
   
   a_counter = func_a();
   b_counter = func_b(); 
   
   myprintf("Finished\n"); 
   
   if (a_counter != 0xacd)
      myprintf("FAIL: a_counter is 0x%x\n", a_counter);
   else if (b_counter != 0xbacdd)
      myprintf("FAIL: b_counter is 0x%x\n", b_counter);
   else if (my_funca_addr != yo_funca_addr)
      myprintf("FAIL: my_funca at '0x%lx'; yo_funca at '0x%lx\n",
             my_funca_addr, yo_funca_addr);
   else
      myprintf("PASS\n");

   return 0;
}
