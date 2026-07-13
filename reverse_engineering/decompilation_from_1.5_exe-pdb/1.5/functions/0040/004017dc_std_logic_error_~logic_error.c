/*
 * Entry: 004017dc
 * Name: std::logic_error::~logic_error
 * Namespace: std::logic_error
 * Signature: void ~logic_error(logic_error * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall std::logic_error::~logic_error(logic_error *this)

{
  this->_padding_ = (int)&_vftable_;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &this->_Str);
  this->_padding_ = (int)&stdext::exception::_vftable_;
  return;
}
