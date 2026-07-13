/*
 * Entry: 0055972c
 * Name: SyncGamePlayerList::AllReady
 * Namespace: SyncGamePlayerList
 * Signature: bool AllReady(SyncGamePlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SyncGamePlayerList::AllReady(SyncGamePlayerList *this)

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
    if (bVar1) {
      return true;
    }
    ppPVar2 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*(&local_c);
    if ((*ppPVar2)->launched == false) break;
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_c);
    ppPVar2 = (Player **)this->_padding_;
  }
  return false;
}
