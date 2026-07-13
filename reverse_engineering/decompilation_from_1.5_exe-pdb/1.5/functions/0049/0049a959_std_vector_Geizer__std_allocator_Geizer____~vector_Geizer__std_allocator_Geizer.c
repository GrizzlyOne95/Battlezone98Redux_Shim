/*
 * Entry: 0049a959
 * Name: std::vector<Geizer_*,std::allocator<Geizer_*>_>::~vector<Geizer_*,std::allocator<Geizer_*>_>
 * Namespace: std::vector<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: void ~vector<Geizer_*,std::allocator<Geizer_*>_>(vector<Geizer_*,std::allocator<Geizer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Geizer_*,std::allocator<Geizer_*>_>::~vector<Geizer_*,std::allocator<Geizer_*>_>
          (vector<Geizer_*,std::allocator<Geizer_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
