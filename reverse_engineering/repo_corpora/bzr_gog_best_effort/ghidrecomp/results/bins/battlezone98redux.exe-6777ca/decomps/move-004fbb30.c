
/* Library Function - Multiple Matches With Same Base Name
    public: static unsigned short * __cdecl std::char_traits<unsigned short>::move(unsigned short
   *,unsigned short const *,unsigned int)
    public: static wchar_t * __cdecl std::char_traits<wchar_t>::move(wchar_t *,wchar_t const
   *,unsigned int)
   
   Library: Visual Studio 2012 Release */

undefined4 __thiscall move(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  if (param_4 != 0) {
    param_2 = FUN_004fbb10(param_2,param_3,param_4,param_1);
  }
  return param_2;
}

