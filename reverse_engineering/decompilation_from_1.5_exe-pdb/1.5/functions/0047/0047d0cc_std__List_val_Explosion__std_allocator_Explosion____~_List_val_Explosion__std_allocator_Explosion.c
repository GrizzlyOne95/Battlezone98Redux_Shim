/*
 * Entry: 0047d0cc
 * Name: std::_List_val<Explosion_*,std::allocator<Explosion_*>_>::~_List_val<Explosion_*,std::allocator<Explosion_*>_>
 * Namespace: std::_List_val<Explosion_*,std::allocator<Explosion_*>_>
 * Signature: void ~_List_val<Explosion_*,std::allocator<Explosion_*>_>(_List_val<Explosion_*,std::allocator<Explosion_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_val<Explosion_*,std::allocator<Explosion_*>_>::
~_List_val<Explosion_*,std::allocator<Explosion_*>_>
          (_List_val<Explosion_*,std::allocator<Explosion_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
