/*
 * Entry: 005353de
 * Name: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::~vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Namespace: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: void ~vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>(vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::
~vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
          (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
