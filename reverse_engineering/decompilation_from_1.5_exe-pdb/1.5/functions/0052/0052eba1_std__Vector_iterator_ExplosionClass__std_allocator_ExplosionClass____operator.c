/*
 * Entry: 0052eba1
 * Name: std::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::operator+=
 * Namespace: std::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: _Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * operator+=(_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * __thiscall
std::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::operator+=
          (_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this,int param_1)

{
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::operator+=
            ((_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *)this,
             param_1);
  return this;
}
