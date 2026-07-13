/*
 * Entry: 0044f5b0
 * Name: std::vector<Strip_*,std::allocator<Strip_*>_>::_Xlen
 * Namespace: std::vector<Strip_*,std::allocator<Strip_*>_>
 * Signature: void _Xlen(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl std::vector<Strip_*,std::allocator<Strip_*>_>::_Xlen(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_40 [28];
  exception local_24;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_1c [28];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_40,"vector<T> too long");
  local_24._Ptr = "unknown";
  local_24._padding_ = (int)&logic_error::_vftable_;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_1c,local_40);
  local_24._padding_ = (int)&length_error::_vftable_;
  if (_DAT_00225350 != (code *)0x0) {
    (*_DAT_00225350)(&local_24);
  }
  (**(code **)(local_24._padding_ + 8))();
  std::_Throw(&local_24);
  local_24._padding_ = (int)&logic_error::_vftable_;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_1c);
  local_24._padding_ = (int)&stdext::exception::_vftable_;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_40);
  return;
}
