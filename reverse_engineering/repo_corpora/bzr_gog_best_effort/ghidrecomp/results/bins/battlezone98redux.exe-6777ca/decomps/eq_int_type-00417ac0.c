
/* Library Function - Multiple Matches With Same Base Name
    public: static bool __cdecl std::_Narrow_char_traits<char,int>::eq_int_type(int const &,int
   const &)
    public: static bool __cdecl std::char_traits<char>::eq_int_type(int const &,int const &)
   
   Libraries: Visual Studio 2012, Visual Studio 2015, Visual Studio 2017, Visual Studio 2019 */

bool eq_int_type(int *param_1,int *param_2)

{
  return *param_1 == *param_2;
}

