/*
 * Entry: 0055934a
 * Name: PlayerList::Timer
 * Namespace: PlayerList
 * Signature: void Timer(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::Timer(PlayerList *this)

{
  vector<Player_*,std::allocator<Player_*>_> *pvVar1;
  DWORD DVar2;
  bool bVar3;
  Player **ppPVar4;
  int iVar5;
  Player *pPVar6;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_18;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_10;
  DWORD local_8;
  
  local_8 = Get_TimeNow();
  pvVar1 = &this->playerV;
  std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            (&local_18,(this->playerV)._Myfirst,(_Container_base_aux *)pvVar1);
  local_10._padding_ = local_18._padding_;
  local_10._Myptr = local_18._Myptr;
  std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            (&local_18,(this->playerV)._Mylast,(_Container_base_aux *)pvVar1);
  bVar3 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                    (&local_10,&local_18);
  if (bVar3) {
    pPVar6 = (Player *)0x0;
  }
  else {
    ppPVar4 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*(&local_10);
    pPVar6 = *ppPVar4;
  }
  ppPVar4 = (this->playerV)._Mylast;
  while( true ) {
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
    _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
              (&local_18,ppPVar4,(_Container_base_aux *)pvVar1);
    bVar3 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                      (&local_10,&local_18);
    DVar2 = local_8;
    if (bVar3) break;
    ppPVar4 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*(&local_10);
    if ((*ppPVar4)->dwLastPingSendTime < pPVar6->dwLastPingSendTime) {
      pPVar6 = *ppPVar4;
    }
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_10);
    ppPVar4 = (this->playerV)._Mylast;
  }
  if ((pPVar6 != (Player *)0x0) && (pPVar6->dwLastPingSendTime + 10000 < local_8)) {
    iVar5 = dpPingUser(this->dp,pPVar6->id,this->dp_karma_unique,this->PingHandler);
    if (iVar5 == 0) {
      pPVar6->dwLastPingSendTime = DVar2;
      pPVar6->dp_karma = this->dp_karma_unique;
      this->dp_karma_unique = this->dp_karma_unique + 1;
    }
  }
  return;
}
