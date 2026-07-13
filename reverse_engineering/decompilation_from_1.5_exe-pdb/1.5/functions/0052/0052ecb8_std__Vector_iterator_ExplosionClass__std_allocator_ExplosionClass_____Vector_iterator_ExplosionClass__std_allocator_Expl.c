/*
 * Entry: 0052ecb8
 * Name: std::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Namespace: std::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: _Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * _Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>(_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this, ExplosionClass * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * __thiscall
std::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
          (_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this,
          ExplosionClass **param_1,_Container_base_aux *param_2)

{
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
  _Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
            ((_Vector_const_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *)this,
             param_1,param_2);
  return this;
}
