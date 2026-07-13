/*
 * Entry: 00408a26
 * Name: std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++
 * Namespace: std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * operator++(_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * __thiscall
std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++
          (_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> *this)

{
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++
            ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)this);
  return this;
}
