/*
 * Entry: 00558c66
 * Name: PlayerList::IsHost
 * Namespace: PlayerList
 * Signature: bool IsHost(PlayerList * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __thiscall PlayerList::IsHost(PlayerList *this,ushort param_1)

{
  bool bVar1;
  Player **ppPVar2;
  undefined4 local_7c;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_78;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_70;
  undefined1 local_68 [21];
  byte local_53;
  byte local_19;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (this->dp != (dp_s *)0x0) {
    local_7c = 0x5f;
    dp_result = dpGetSessionDesc(this->dp,local_68,&local_7c);
    if ((dp_result == 0) &&
       (((local_53 & 0x10) == 0 || (((local_19 & 2) == 0 && ((local_53 & 8) == 0)))))) {
      std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
      _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
                (&local_70,(this->playerV)._Myfirst,(_Container_base_aux *)&this->playerV);
      local_78._padding_ = local_70._padding_;
      ppPVar2 = (this->playerV)._Mylast;
      local_78._Myptr = local_70._Myptr;
      while( true ) {
        std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
        _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
                  (&local_70,ppPVar2,(_Container_base_aux *)&this->playerV);
        bVar1 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                          (&local_78,&local_70);
        if (bVar1) {
          return true;
        }
        ppPVar2 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*
                            (&local_78);
        if ((*ppPVar2)->id < param_1) break;
        std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_78);
        ppPVar2 = (this->playerV)._Mylast;
      }
    }
  }
  return false;
}
