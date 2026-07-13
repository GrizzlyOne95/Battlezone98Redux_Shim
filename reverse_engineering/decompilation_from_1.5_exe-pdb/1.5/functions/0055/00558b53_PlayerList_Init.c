/*
 * Entry: 00558b53
 * Name: PlayerList::Init
 * Namespace: PlayerList
 * Signature: void Init(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::Init(PlayerList *this)

{
  bool bVar1;
  Player **ppPVar2;
  WPARAM wParam;
  LRESULT LVar3;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_18;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_10;
  Player *local_8;
  
  if ((HWND)this->hList != (HWND)0x0) {
    SendMessageA((HWND)this->hList,0x184,0,0);
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
    _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
              (&local_18,(this->playerV)._Myfirst,(_Container_base_aux *)&this->playerV);
    local_10._padding_ = local_18._padding_;
    ppPVar2 = (this->playerV)._Mylast;
    local_10._Myptr = local_18._Myptr;
    while( true ) {
      std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
      _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
                (&local_18,ppPVar2,(_Container_base_aux *)&this->playerV);
      bVar1 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                        (&local_10,&local_18);
      if (bVar1) break;
      ppPVar2 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*
                          (&local_10);
      local_8 = *ppPVar2;
      wParam = SendMessageA((HWND)this->hList,0x180,0,(LPARAM)local_8);
      this->l = wParam;
      LVar3 = SendMessageA((HWND)this->hList,0x19a,wParam,(uint)local_8->id);
      this->l = LVar3;
      std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_10);
      ppPVar2 = (this->playerV)._Mylast;
    }
    Redraw(this);
  }
  return;
}
