/*
 * Entry: 005576b4
 * Name: std::_Vector_val<Player_*,std::allocator<Player_*>_>::~_Vector_val<Player_*,std::allocator<Player_*>_>
 * Namespace: std::_Vector_val<Player_*,std::allocator<Player_*>_>
 * Signature: void ~_Vector_val<Player_*,std::allocator<Player_*>_>(_Vector_val<Player_*,std::allocator<Player_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<Player_*,std::allocator<Player_*>_>::
~_Vector_val<Player_*,std::allocator<Player_*>_>
          (_Vector_val<Player_*,std::allocator<Player_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
