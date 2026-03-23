
/* Library Function - Multiple Matches With Same Base Name
    public: static int __cdecl std::_Narrow_char_traits<char,int>::not_eof(int const &)
    public: static int __cdecl std::char_traits<char>::not_eof(int const &)
   
   Libraries: Visual Studio 2012, Visual Studio 2015, Visual Studio 2017, Visual Studio 2019 */

uint not_eof(uint *param_1)

{
  uint uVar1;
  int iVar2;
  int in_stack_fffffff4;
  uint local_8;
  
  uVar1 = eof(in_stack_fffffff4);
  if (*param_1 == uVar1) {
    iVar2 = eof(in_stack_fffffff4);
    local_8 = (uint)(iVar2 == 0);
  }
  else {
    local_8 = *param_1;
  }
  return local_8;
}

