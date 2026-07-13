/*
 * Entry: 00557dd4
 * Name: std::_Vector_iterator<Player_*,std::allocator<Player_*>_>::_Vector_iterator<Player_*,std::allocator<Player_*>_>
 * Namespace: std::_Vector_iterator<Player_*,std::allocator<Player_*>_>
 * Signature: _Vector_iterator<Player_*,std::allocator<Player_*>_> * _Vector_iterator<Player_*,std::allocator<Player_*>_>(_Vector_iterator<Player_*,std::allocator<Player_*>_> * this, Player * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Player_*,std::allocator<Player_*>_> * __thiscall
std::_Vector_iterator<Player_*,std::allocator<Player_*>_>::
_Vector_iterator<Player_*,std::allocator<Player_*>_>
          (_Vector_iterator<Player_*,std::allocator<Player_*>_> *this,Player **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            ((_Vector_const_iterator<Player_*,std::allocator<Player_*>_> *)this,param_1,param_2);
  return this;
}
