/*
 * Entry: 0052ec47
 * Name: std::_Vector_val<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::~_Vector_val<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Namespace: std::_Vector_val<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: void ~_Vector_val<ExplosionClass_*,std::allocator<ExplosionClass_*>_>(_Vector_val<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
~_Vector_val<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
          (_Vector_val<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
