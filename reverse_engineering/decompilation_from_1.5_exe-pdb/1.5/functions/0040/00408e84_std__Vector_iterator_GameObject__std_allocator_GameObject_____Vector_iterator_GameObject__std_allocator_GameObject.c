/*
 * Entry: 00408e84
 * Name: std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>
 * Namespace: std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>(_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * this, GameObject * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * __thiscall
std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>::
_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>
          (_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> *this,GameObject **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)this,param_1,
             param_2);
  return this;
}
