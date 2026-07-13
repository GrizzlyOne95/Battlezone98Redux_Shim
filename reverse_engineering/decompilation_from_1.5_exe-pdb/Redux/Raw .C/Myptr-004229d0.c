
/* Library Function - Multiple Matches With Same Base Name
    public: unsigned short * __thiscall std::_String_val<struct std::_Simple_types<unsigned short>
   >::_Myptr(void)
    public: wchar_t * __thiscall std::_String_val<struct std::_Simple_types<wchar_t> >::_Myptr(void)
   
   Library: Visual Studio 2012 Release */

undefined4 * __fastcall Myptr(undefined4 *param_1)

{
  undefined4 *local_c;
  
  local_c = param_1;
  if (7 < (uint)param_1[5]) {
    local_c = (undefined4 *)FUN_00417780(*param_1);
  }
  return local_c;
}

