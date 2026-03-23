
/* Library Function - Multiple Matches With Same Base Name
    public: static unsigned short * __cdecl std::char_traits<unsigned short>::copy(unsigned short
   *,unsigned short const *,unsigned int)
    public: static wchar_t * __cdecl std::char_traits<wchar_t>::copy(wchar_t *,wchar_t const
   *,unsigned int)
   
   Library: Visual Studio 2012 Release */

wchar_t * copy(wchar_t *param_1,wchar_t *param_2,size_t param_3)

{
  undefined4 local_8;
  
  if (param_3 == 0) {
    local_8 = param_1;
  }
  else {
    local_8 = FID_conflict__wmemcpy(param_1,param_2,param_3);
  }
  return local_8;
}

