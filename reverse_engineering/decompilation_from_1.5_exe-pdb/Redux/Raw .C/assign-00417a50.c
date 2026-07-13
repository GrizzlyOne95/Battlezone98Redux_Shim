
/* Library Function - Single Match
    public: static char * __cdecl std::char_traits<char>::assign(char *,unsigned int,char)
   
   Libraries: Visual Studio 2008, Visual Studio 2010, Visual Studio 2012, Visual Studio 2015 */

char * __cdecl std::char_traits<char>::assign(char *param_1,uint param_2,char param_3)

{
  char *pcVar1;
  
  pcVar1 = memset(param_1,(int)param_3,param_2);
  return pcVar1;
}

