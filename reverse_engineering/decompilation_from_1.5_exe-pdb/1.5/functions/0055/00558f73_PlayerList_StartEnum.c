/*
 * Entry: 00558f73
 * Name: PlayerList::StartEnum
 * Namespace: PlayerList
 * Signature: void StartEnum(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::StartEnum(PlayerList *this)

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
    if (bVar1) break;
    ppPVar2 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*(&local_c);
    (*ppPVar2)->mark = 0;
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_c);
    ppPVar2 = (this->playerV)._Mylast;
  }
  this->bInEnum = true;
  return;
}
