/*
 * Entry: 00559423
 * Name: PlayerList::Ping
 * Namespace: PlayerList
 * Signature: void Ping(PlayerList * this, short param_1, long param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::Ping(PlayerList *this,short param_1,long param_2,int param_3)

{
  Player *pPVar1;
  bool bVar2;
  Player **ppPVar3;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_14;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_c;
  
  std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
            (&local_14,(this->playerV)._Myfirst,(_Container_base_aux *)&this->playerV);
  local_c._padding_ = local_14._padding_;
  ppPVar3 = (this->playerV)._Mylast;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
    _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
              (&local_14,ppPVar3,(_Container_base_aux *)&this->playerV);
    bVar2 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar2) {
      return;
    }
    ppPVar3 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*(&local_c);
    pPVar1 = *ppPVar3;
    if (pPVar1->dp_karma == param_1) break;
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_c);
    ppPVar3 = (this->playerV)._Mylast;
  }
  if ((pPVar1->avg_ms == param_2) && (pPVar1->loss_pct == param_3)) {
    return;
  }
  pPVar1->avg_ms = param_2;
  pPVar1->loss_pct = param_3;
  ModifyListItem(this,pPVar1);
  return;
}
