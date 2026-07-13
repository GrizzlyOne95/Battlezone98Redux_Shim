/*
 * Entry: 0052eb46
 * Name: std::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::operator++
 * Namespace: std::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: _Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * operator++(_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * __thiscall
std::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::operator++
          (_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this)

{
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::operator++
            ((_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *)this);
  return this;
}
