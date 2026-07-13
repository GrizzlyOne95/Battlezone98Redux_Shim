/*
 * Entry: 0055c617
 * Name: ServerList::Enum
 * Namespace: ServerList
 * Signature: void Enum(ServerList * this, char * param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ServerList::Enum(ServerList *this,char *param_1,long param_2,long param_3)

{
  vector<Server_*,std::allocator<Server_*>_> *this_00;
  byte bVar1;
  bool bVar2;
  Server **ppSVar3;
  Server *pSVar4;
  Server *pSVar5;
  int iVar6;
  byte *pbVar7;
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> local_14;
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> local_c;
  
  this_00 = &this->serverV;
  std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
            (&local_14,(this->serverV)._Myfirst,(_Container_base_aux *)this_00);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
            (&local_14,(this->serverV)._Mylast,(_Container_base_aux *)this_00);
  bVar2 = std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator==
                    (&local_c,&local_14);
  do {
    if (bVar2) {
LAB_0055c6dd:
      std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
      _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
                (&local_14,(this->serverV)._Mylast,(_Container_base_aux *)this_00);
      bVar2 = std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator==
                        (&local_c,&local_14);
      if (bVar2) {
        pSVar4 = operator_new(0x8c);
        if (pSVar4 == (Server *)0x0) {
          param_3 = 0;
        }
        else {
          param_3 = (long)Server::Server(pSVar4,param_1,param_2,param_3);
        }
        std::vector<Server_*,std::allocator<Server_*>_>::push_back(this_00,(Server **)&param_3);
        AddListItem(this,(Server *)param_3);
      }
      this->bEnumed = true;
      return;
    }
    ppSVar3 = std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator*(&local_c);
    pSVar4 = *ppSVar3;
    pSVar5 = pSVar4;
    pbVar7 = (byte *)param_1;
    do {
      bVar1 = pSVar5->caName[0];
      bVar2 = bVar1 < *pbVar7;
      if (bVar1 != *pbVar7) {
LAB_0055c68a:
        iVar6 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
        goto LAB_0055c68f;
      }
      if (bVar1 == 0) break;
      bVar1 = pSVar5->caName[1];
      bVar2 = bVar1 < pbVar7[1];
      if (bVar1 != pbVar7[1]) goto LAB_0055c68a;
      pSVar5 = (Server *)(pSVar5->caName + 2);
      pbVar7 = pbVar7 + 2;
    } while (bVar1 != 0);
    iVar6 = 0;
LAB_0055c68f:
    if (iVar6 == 0) {
      pSVar4->avg_ms = param_2;
      pSVar4->nr_pl = param_3;
      pSVar4->mark = 0x14;
      Redraw(this);
      goto LAB_0055c6dd;
    }
    std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator++(&local_c);
    std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
    _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
              (&local_14,(this->serverV)._Mylast,(_Container_base_aux *)this_00);
    bVar2 = std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator==
                      (&local_c,&local_14);
  } while( true );
}
