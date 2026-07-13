/*
 * Entry: 00558d90
 * Name: PlayerList::FindPlayerID
 * Namespace: PlayerList
 * Signature: ushort FindPlayerID(PlayerList * this, char * param_1, char * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort __thiscall PlayerList::FindPlayerID(PlayerList *this,char *param_1,char **param_2)

{
  Player *_Str1;
  char *pcVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  Player **ppPVar5;
  Player *pPVar6;
  char *pcVar7;
  vector<Player_*,std::allocator<Player_*>_> *pvVar8;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_1c;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_14;
  char *local_c;
  uint local_8;
  
  if (param_2 != (char **)0x0) {
    *param_2 = (char *)0x0;
  }
  local_8 = 0xfa01;
  pcVar7 = param_1;
  while ((*pcVar7 != '\0' && (iVar4 = isspace((int)*pcVar7), iVar4 != 0))) {
    pcVar7 = pcVar7 + 1;
  }
  iVar4 = sscanf(pcVar7,"#%d",&local_8);
  if (iVar4 == 0) {
    param_1 = (char *)0x0;
    pvVar8 = &this->playerV;
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
    _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
              (&local_1c,(this->playerV)._Myfirst,(_Container_base_aux *)pvVar8);
    local_14._padding_ = local_1c._padding_;
    local_14._Myptr = local_1c._Myptr;
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
    _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
              (&local_1c,(this->playerV)._Mylast,(_Container_base_aux *)pvVar8);
    bVar3 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                      (&local_14,&local_1c);
    while (!bVar3) {
      ppPVar5 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*
                          (&local_14);
      _Str1 = *ppPVar5;
      pPVar6 = _Str1;
      do {
        pcVar1 = pPVar6->caName;
        pPVar6 = (Player *)(pPVar6->caName + 1);
      } while (*pcVar1 != '\0');
      local_c = (char *)((int)pPVar6 - (int)(_Str1->caName + 1));
      if ((param_1 < local_c) && (iVar4 = strncmp(_Str1->caName,pcVar7,(size_t)local_c), iVar4 == 0)
         ) {
        param_1 = local_c;
        local_8 = (uint)_Str1->id;
      }
      std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_14);
      std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
      _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
                (&local_1c,(this->playerV)._Mylast,(_Container_base_aux *)pvVar8);
      bVar3 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                        (&local_14,&local_1c);
    }
    pcVar7 = pcVar7 + (int)param_1;
    while ((pcVar7 != (char *)0x0 && (iVar4 = isspace((int)*pcVar7), iVar4 != 0))) {
      pcVar7 = pcVar7 + 1;
    }
    if (param_2 != (char **)0x0) {
      *param_2 = pcVar7;
    }
  }
  else {
    cVar2 = *pcVar7;
    if (cVar2 != '\0') {
      do {
        iVar4 = isspace((int)cVar2);
        if (iVar4 != 0) break;
        pcVar7 = pcVar7 + 1;
        cVar2 = *pcVar7;
      } while (cVar2 != '\0');
      while ((*pcVar7 != '\0' && (iVar4 = isspace((int)*pcVar7), iVar4 != 0))) {
        pcVar7 = pcVar7 + 1;
      }
    }
    if (param_2 != (char **)0x0) {
      *param_2 = pcVar7;
    }
    local_8._0_2_ = (short)local_8 * 4 + 0x28;
  }
  return (ushort)local_8;
}
