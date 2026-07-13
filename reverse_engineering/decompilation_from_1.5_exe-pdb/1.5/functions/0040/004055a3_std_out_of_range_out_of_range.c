/*
 * Entry: 004055a3
 * Name: std::out_of_range::out_of_range
 * Namespace: std::out_of_range
 * Signature: out_of_range * out_of_range(out_of_range * this, basic_string<char,std::char_traits<char>,std::allocator<char>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

out_of_range * __thiscall
std::out_of_range::out_of_range
          (out_of_range *this,
          basic_string<char,std::char_traits<char>,std::allocator<char>_> *param_1)

{
  logic_error::logic_error((logic_error *)this,param_1);
  *(undefined ***)this = &_vftable_;
  return this;
}
