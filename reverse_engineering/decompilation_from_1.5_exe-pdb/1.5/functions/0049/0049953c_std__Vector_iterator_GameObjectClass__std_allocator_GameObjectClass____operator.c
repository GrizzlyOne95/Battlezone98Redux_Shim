/*
 * Entry: 0049953c
 * Name: std::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator++
 * Namespace: std::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: _Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * operator++(_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * __thiscall
std::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator++
          (_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this)

{
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator++
            ((_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *)this);
  return this;
}
