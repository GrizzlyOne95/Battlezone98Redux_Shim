/*
 * Entry: 0055ad74
 * Name: ServerList::EndEnum
 * Namespace: ServerList
 * Signature: void EndEnum(ServerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall ServerList::EndEnum(ServerList *this)

{
  vector<Server_*,std::allocator<Server_*>_> *this_00;
  char cVar1;
  int iVar2;
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> _Var3;
  bool bVar4;
  Server **ppSVar5;
  LRESULT LVar6;
  char *pcVar7;
  Server *pSVar8;
  char *pcVar9;
  Server *pSVar10;
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> local_1c;
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> local_14;
  Server *local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  this_00 = &this->serverV;
  std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
            (&local_14,(this->serverV)._Myfirst,(_Container_base_aux *)this_00);
  if (((int)(this->serverV)._Mylast - (int)(this->serverV)._Myfirst & 0xfffffffcU) == 0) {
    local_c = (Server *)0x0;
  }
  else {
    ppSVar5 = std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator*(&local_14);
    local_c = *ppSVar5;
  }
  std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
            (&local_1c,(this->serverV)._Myfirst,(_Container_base_aux *)this_00);
  local_14._padding_ = local_1c._padding_;
  ppSVar5 = (this->serverV)._Mylast;
  local_14._Myptr = local_1c._Myptr;
  while( true ) {
    std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
    _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
              (&local_1c,ppSVar5,(_Container_base_aux *)this_00);
    bVar4 = std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator==
                      (&local_14,&local_1c);
    if (bVar4) break;
    ppSVar5 = std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator*(&local_14);
    pSVar8 = *ppSVar5;
    if (pSVar8->mark < 0) {
      DeleteListItem(this,pSVar8);
      operator_delete(pSVar8);
      _Var3._Myptr = (Server **)local_14._padding_;
      _Var3._padding_ = (int)&local_1c;
      std::vector<Server_*,std::allocator<Server_*>_>::erase(this_00,_Var3);
      break;
    }
    if (pSVar8->avg_ms < local_c->avg_ms) {
      local_c = pSVar8;
    }
    std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator++(&local_14);
    ppSVar5 = (this->serverV)._Mylast;
  }
  pcVar9 = (char *)0x0;
  LVar6 = SendMessageA((HWND)this->hList,0x188,0,0);
  if (LVar6 != -1) goto LAB_0055aed3;
  pcVar7 = Net::hostname;
  do {
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  if (pcVar7 == Net::hostname + 1) {
    pSVar8 = local_c;
    if (local_c != (Server *)0x0) {
      do {
        pcVar9 = pSVar8->caName;
        pSVar8 = (Server *)(pSVar8->caName + 1);
        pSVar10 = local_c;
      } while (*pcVar9 != '\0');
      goto LAB_0055aeac;
    }
  }
  else {
    pcVar9 = Net::hostname;
    do {
      cVar1 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar1 != '\0');
    pSVar10 = (Server *)Net::hostname;
LAB_0055aeac:
    pcVar9 = &stack0xffffffd4;
    sprintf(pcVar9,"%s ",pSVar10);
  }
  SendMessageA((HWND)this->hList,0x18c,0xffffffff,(LPARAM)pcVar9);
  Redraw(this);
LAB_0055aed3:
  iVar2 = this->fastEnums;
  if (iVar2 < 1) {
    if (iVar2 == 0) {
      this->fastEnums = -1;
      this->enumDelay = 10000;
    }
  }
  else if (this->bEnumed != false) {
    this->fastEnums = iVar2 + -1;
  }
  this->bInEnumServers = false;
  return;
}
