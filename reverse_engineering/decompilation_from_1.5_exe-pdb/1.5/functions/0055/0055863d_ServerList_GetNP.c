/*
 * Entry: 0055863d
 * Name: ServerList::GetNP
 * Namespace: ServerList
 * Signature: char * GetNP(ServerList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall ServerList::GetNP(ServerList *this,char *param_1)

{
  vector<Server_*,std::allocator<Server_*>_> *pvVar1;
  char *_Dest;
  byte bVar2;
  bool bVar3;
  Server **ppSVar4;
  Server *pSVar5;
  int iVar6;
  byte *pbVar7;
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> local_14;
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> local_c;
  
  pvVar1 = &this->serverV;
  _Dest = this->pcNp;
  *_Dest = '\0';
  std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
            (&local_14,(this->serverV)._Myfirst,(_Container_base_aux *)pvVar1);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
            (&local_14,(this->serverV)._Mylast,(_Container_base_aux *)pvVar1);
  bVar3 = std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator==
                    (&local_c,&local_14);
  do {
    if (bVar3) {
      return _Dest;
    }
    ppSVar4 = std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator*(&local_c);
    pSVar5 = *ppSVar4;
    pbVar7 = (byte *)param_1;
    do {
      bVar2 = pSVar5->caName[0];
      bVar3 = bVar2 < *pbVar7;
      if (bVar2 != *pbVar7) {
LAB_005586b0:
        iVar6 = (1 - (uint)bVar3) - (uint)(bVar3 != 0);
        goto LAB_005586b5;
      }
      if (bVar2 == 0) break;
      bVar2 = pSVar5->caName[1];
      bVar3 = bVar2 < pbVar7[1];
      if (bVar2 != pbVar7[1]) goto LAB_005586b0;
      pSVar5 = (Server *)(pSVar5->caName + 2);
      pbVar7 = pbVar7 + 2;
    } while (bVar2 != 0);
    iVar6 = 0;
LAB_005586b5:
    if (iVar6 == 0) {
      sprintf(_Dest,"%d",(*ppSVar4)->nr_pl);
      return _Dest;
    }
    std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator++(&local_c);
    std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
    _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
              (&local_14,(this->serverV)._Mylast,(_Container_base_aux *)pvVar1);
    bVar3 = std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator==
                      (&local_c,&local_14);
  } while( true );
}
