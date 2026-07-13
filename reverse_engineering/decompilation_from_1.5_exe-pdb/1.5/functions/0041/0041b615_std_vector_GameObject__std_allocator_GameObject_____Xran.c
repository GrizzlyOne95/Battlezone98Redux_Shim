/*
 * Entry: 0041b615
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::_Xran
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: void _Xran(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::vector<GameObject_*,std::allocator<GameObject_*>_>::_Xran(void)

{
  logic_error local_44;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_20;
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &local_20,"invalid vector<T> subscript");
  logic_error::logic_error(&local_44,&local_20);
  local_44._padding_ = (int)&out_of_range::_vftable_;
  stdext::exception::_Raise((exception *)&local_44);
  local_44._padding_ = (int)&out_of_range::_vftable_;
  logic_error::~logic_error(&local_44);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &local_20);
  return;
}
