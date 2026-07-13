/*
 * Entry: 00497798
 * Name: std::_Vector_val<GameObject_*,std::allocator<GameObject_*>_>::~_Vector_val<GameObject_*,std::allocator<GameObject_*>_>
 * Namespace: std::_Vector_val<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: void ~_Vector_val<GameObject_*,std::allocator<GameObject_*>_>(_Vector_val<GameObject_*,std::allocator<GameObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<GameObject_*,std::allocator<GameObject_*>_>::
~_Vector_val<GameObject_*,std::allocator<GameObject_*>_>
          (_Vector_val<GameObject_*,std::allocator<GameObject_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
