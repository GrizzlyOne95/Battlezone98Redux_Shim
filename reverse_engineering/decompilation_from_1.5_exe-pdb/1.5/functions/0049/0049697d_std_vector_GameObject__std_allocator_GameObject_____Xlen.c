/*
 * Entry: 0049697d
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::_Xlen
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: void _Xlen(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::vector<GameObject_*,std::allocator<GameObject_*>_>::_Xlen(void)

{
  logic_error local_44;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_20;
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &local_20,"vector<T> too long");
  logic_error::logic_error(&local_44,&local_20);
  local_44._padding_ = (int)&length_error::_vftable_;
  stdext::exception::_Raise((exception *)&local_44);
  local_44._padding_ = (int)&length_error::_vftable_;
  logic_error::~logic_error(&local_44);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &local_20);
  return;
}
