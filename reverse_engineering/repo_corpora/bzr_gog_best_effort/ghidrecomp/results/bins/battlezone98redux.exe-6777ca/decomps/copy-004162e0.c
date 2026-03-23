
/* Library Function - Single Match
    public: static char * __cdecl std::char_traits<char>::copy(char *,char const *,unsigned int)
   
   Library: Visual Studio 2012 Release */

char * __cdecl std::char_traits<char>::copy(char *param_1,char *param_2,uint param_3)

{
  undefined4 local_8;
  
  if (param_3 == 0) {
    local_8 = param_1;
  }
  else {
    local_8 = memcpy(param_1,param_2,param_3);
  }
  return local_8;
}

