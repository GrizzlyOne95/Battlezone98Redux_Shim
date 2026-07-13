/*
 * Entry: 0041cb73
 * Name: std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator+=
 * Namespace: std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * operator+=(_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * __thiscall
std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator+=
          (_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> *this,int param_1)

{
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator+=
            ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)this,param_1);
  return this;
}
