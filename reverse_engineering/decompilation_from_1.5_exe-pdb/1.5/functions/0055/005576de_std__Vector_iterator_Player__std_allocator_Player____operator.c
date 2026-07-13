/*
 * Entry: 005576de
 * Name: std::_Vector_iterator<Player_*,std::allocator<Player_*>_>::operator++
 * Namespace: std::_Vector_iterator<Player_*,std::allocator<Player_*>_>
 * Signature: _Vector_iterator<Player_*,std::allocator<Player_*>_> * operator++(_Vector_iterator<Player_*,std::allocator<Player_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Player_*,std::allocator<Player_*>_> * __thiscall
std::_Vector_iterator<Player_*,std::allocator<Player_*>_>::operator++
          (_Vector_iterator<Player_*,std::allocator<Player_*>_> *this)

{
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++
            ((_Vector_const_iterator<Player_*,std::allocator<Player_*>_> *)this);
  return this;
}
