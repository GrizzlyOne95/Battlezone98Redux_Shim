
/* Library Function - Multiple Matches With Same Base Name
    public: static bool __cdecl std::_Narrow_char_traits<char,int>::eq(char const &,char const &)
    public: static bool __cdecl std::char_traits<char>::eq(char const &,char const &)
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

undefined4 eq(char *param_1,char *param_2)

{
  return CONCAT31(*param_2 >> 7,*param_1 == *param_2);
}

