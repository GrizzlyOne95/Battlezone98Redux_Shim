/*
 * Entry: 00558bff
 * Name: PlayerList::FindPlayer
 * Namespace: PlayerList
 * Signature: Player * FindPlayer(PlayerList * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player * __thiscall PlayerList::FindPlayer(PlayerList *this,ushort param_1)

{
  bool bVar1;
  Player **ppPVar2;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_14;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_c;
  
  std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            (&local_14,(this->playerV)._Myfirst,(_Container_base_aux *)&this->playerV);
  local_c._padding_ = local_14._padding_;
  ppPVar2 = (this->playerV)._Mylast;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
    _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
              (&local_14,ppPVar2,(_Container_base_aux *)&this->playerV);
    bVar1 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar1) {
      return (Player *)0x0;
    }
    ppPVar2 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*(&local_c);
    if (param_1 == (*ppPVar2)->id) break;
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_c);
    ppPVar2 = (this->playerV)._Mylast;
  }
  return *ppPVar2;
}
