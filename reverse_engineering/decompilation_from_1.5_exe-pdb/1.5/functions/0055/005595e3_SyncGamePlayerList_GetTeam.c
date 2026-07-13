/*
 * Entry: 005595e3
 * Name: SyncGamePlayerList::GetTeam
 * Namespace: SyncGamePlayerList
 * Signature: int GetTeam(SyncGamePlayerList * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall SyncGamePlayerList::GetTeam(SyncGamePlayerList *this,ushort param_1)

{
  int *piVar1;
  Player *pPVar2;
  bool bVar3;
  uint uVar4;
  Player **ppPVar5;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_24;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_1c;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_14;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_c;
  
  if (param_1 == 0xfa01) {
    uVar4 = 0xffffffff;
  }
  else {
    uVar4 = 1;
    piVar1 = &this->_padding_;
    do {
      std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
      _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
                (&local_1c,(Player **)this->_padding_,(_Container_base_aux *)piVar1);
      local_c._padding_ = local_1c._padding_;
      ppPVar5 = (Player **)this->_padding_;
      local_c._Myptr = local_1c._Myptr;
      while( true ) {
        std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
        _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
                  (&local_14,ppPVar5,(_Container_base_aux *)piVar1);
        bVar3 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                          (&local_c,&local_14);
        if (bVar3) break;
        ppPVar5 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*
                            (&local_c);
        pPVar2 = *ppPVar5;
        if (((int)pPVar2->blob[0] == uVar4) && ((pPVar2->InGame != false || (pPVar2->id < param_1)))
           ) break;
        std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_c);
        ppPVar5 = (Player **)this->_padding_;
      }
      std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
      _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
                (&local_24,(Player **)this->_padding_,(_Container_base_aux *)piVar1);
      bVar3 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                        (&local_c,&local_24);
    } while ((!bVar3) && (uVar4 = uVar4 + 1, (int)uVar4 < 0x10));
    uVar4 = uVar4 & 0xf;
  }
  return uVar4;
}
