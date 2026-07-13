/*
 * Entry: 005594b6
 * Name: GamePlayerList::IsHost
 * Namespace: GamePlayerList
 * Signature: bool IsHost(GamePlayerList * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GamePlayerList::IsHost(GamePlayerList *this,ushort param_1)

{
  bool bVar1;
  Player **ppPVar2;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_14;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_c;
  
  std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            (&local_14,*(Player ***)&this->field_0x20,(_Container_base_aux *)&this->field_0x14);
  local_c._padding_ = local_14._padding_;
  ppPVar2 = *(Player ***)&this->field_0x24;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
    _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
              (&local_14,ppPVar2,(_Container_base_aux *)&this->field_0x14);
    bVar1 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar1) {
      return true;
    }
    ppPVar2 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*(&local_c);
    if ((*ppPVar2)->id < param_1) break;
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_c);
    ppPVar2 = *(Player ***)&this->field_0x24;
  }
  return false;
}
