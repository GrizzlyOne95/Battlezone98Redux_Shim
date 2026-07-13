/*
 * Entry: 005578be
 * Name: std::_Vector_iterator<Player_*,std::allocator<Player_*>_>::operator+=
 * Namespace: std::_Vector_iterator<Player_*,std::allocator<Player_*>_>
 * Signature: _Vector_iterator<Player_*,std::allocator<Player_*>_> * operator+=(_Vector_iterator<Player_*,std::allocator<Player_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Player_*,std::allocator<Player_*>_> * __thiscall
std::_Vector_iterator<Player_*,std::allocator<Player_*>_>::operator+=
          (_Vector_iterator<Player_*,std::allocator<Player_*>_> *this,int param_1)

{
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator+=
            ((_Vector_const_iterator<Player_*,std::allocator<Player_*>_> *)this,param_1);
  return this;
}
