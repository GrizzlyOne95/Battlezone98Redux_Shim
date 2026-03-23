
/* Library Function - Multiple Matches With Same Base Name
    public: static unsigned int __cdecl std::_Narrow_char_traits<char,int>::length(char const *
   const)
    public: static unsigned int __cdecl std::char_traits<char>::length(char const * const)
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

int length(char *param_1)

{
  char cVar1;
  char *local_c;
  
  local_c = param_1;
  do {
    cVar1 = *local_c;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  return (int)local_c - (int)(param_1 + 1);
}

