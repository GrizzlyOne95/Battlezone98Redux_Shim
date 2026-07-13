/*
 * Entry: 004adfff
 * Name: std::vector<Scanner_*,std::allocator<Scanner_*>_>::~vector<Scanner_*,std::allocator<Scanner_*>_>
 * Namespace: std::vector<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: void ~vector<Scanner_*,std::allocator<Scanner_*>_>(vector<Scanner_*,std::allocator<Scanner_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Scanner_*,std::allocator<Scanner_*>_>::~vector<Scanner_*,std::allocator<Scanner_*>_>
          (vector<Scanner_*,std::allocator<Scanner_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
