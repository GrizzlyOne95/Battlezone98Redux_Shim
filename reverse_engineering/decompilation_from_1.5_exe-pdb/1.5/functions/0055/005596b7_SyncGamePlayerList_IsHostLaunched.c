/*
 * Entry: 005596b7
 * Name: SyncGamePlayerList::IsHostLaunched
 * Namespace: SyncGamePlayerList
 * Signature: bool IsHostLaunched(SyncGamePlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SyncGamePlayerList::IsHostLaunched(SyncGamePlayerList *this)

{
  ushort uVar1;
  bool bVar2;
  Player **ppPVar3;
  undefined1 uVar4;
  ushort uVar5;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_14;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_c;
  
  uVar5 = 0xfa01;
  uVar4 = 0;
  std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            (&local_14,(Player **)this->_padding_,(_Container_base_aux *)&this->_padding_);
  local_c._padding_ = local_14._padding_;
  ppPVar3 = (Player **)this->_padding_;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
    _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
              (&local_14,ppPVar3,(_Container_base_aux *)&this->_padding_);
    bVar2 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar2) break;
    ppPVar3 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*(&local_c);
    uVar1 = (*ppPVar3)->id;
    if (uVar1 < uVar5) {
      uVar4 = (*ppPVar3)->hostlaunched;
      uVar5 = uVar1;
    }
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_c);
    ppPVar3 = (Player **)this->_padding_;
  }
  return (bool)uVar4;
}
