/*
 * Entry: 0049a851
 * Name: std::_Vector_val<Geizer_*,std::allocator<Geizer_*>_>::~_Vector_val<Geizer_*,std::allocator<Geizer_*>_>
 * Namespace: std::_Vector_val<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: void ~_Vector_val<Geizer_*,std::allocator<Geizer_*>_>(_Vector_val<Geizer_*,std::allocator<Geizer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<Geizer_*,std::allocator<Geizer_*>_>::
~_Vector_val<Geizer_*,std::allocator<Geizer_*>_>
          (_Vector_val<Geizer_*,std::allocator<Geizer_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
