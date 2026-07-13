/*
 * Entry: 00559791
 * Name: SyncGamePlayerList::Reset
 * Namespace: SyncGamePlayerList
 * Signature: void Reset(SyncGamePlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SyncGamePlayerList::Reset(SyncGamePlayerList *this)

{
  bool bVar1;
  Player **ppPVar2;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_14;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_c;
  
  std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            (&local_14,(Player **)this->_padding_,(_Container_base_aux *)&this->_padding_);
  local_c._padding_ = local_14._padding_;
  ppPVar2 = (Player **)this->_padding_;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
    _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
              (&local_14,ppPVar2,(_Container_base_aux *)&this->_padding_);
    bVar1 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar1) break;
    ppPVar2 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*(&local_c);
    PlayerList::ModifyListItem((PlayerList *)this,*ppPVar2);
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_c);
    ppPVar2 = (Player **)this->_padding_;
  }
  return;
}
