/*
 * Entry: 005597f5
 * Name: SyncGamePlayerList::ReallyReset
 * Namespace: SyncGamePlayerList
 * Signature: void ReallyReset(SyncGamePlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SyncGamePlayerList::ReallyReset(SyncGamePlayerList *this)

{
  Player *pPVar1;
  bool bVar2;
  Player **ppPVar3;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_14;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_c;
  
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
    pPVar1 = *ppPVar3;
    pPVar1->launched = false;
    PlayerList::ModifyListItem((PlayerList *)this,pPVar1);
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_c);
    ppPVar3 = (Player **)this->_padding_;
  }
  return;
}
