/*
 * Entry: 004017b9
 * Name: std::logic_error::logic_error
 * Namespace: std::logic_error
 * Signature: logic_error * logic_error(logic_error * this, basic_string<char,std::char_traits<char>,std::allocator<char>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

logic_error * __thiscall
std::logic_error::logic_error
          (logic_error *this,
          basic_string<char,std::char_traits<char>,std::allocator<char>_> *param_1)

{
  this->_padding_ = (int)"unknown";
  this->_padding_ = (int)&_vftable_;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &this->_Str,
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)param_1
            );
  return this;
}
