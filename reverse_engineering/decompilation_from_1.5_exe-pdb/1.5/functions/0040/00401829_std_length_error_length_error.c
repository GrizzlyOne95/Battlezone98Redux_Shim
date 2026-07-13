/*
 * Entry: 00401829
 * Name: std::length_error::length_error
 * Namespace: std::length_error
 * Signature: length_error * length_error(length_error * this, basic_string<char,std::char_traits<char>,std::allocator<char>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

length_error * __thiscall
std::length_error::length_error
          (length_error *this,
          basic_string<char,std::char_traits<char>,std::allocator<char>_> *param_1)

{
  logic_error::logic_error((logic_error *)this,param_1);
  *(undefined ***)this = &_vftable_;
  return this;
}
