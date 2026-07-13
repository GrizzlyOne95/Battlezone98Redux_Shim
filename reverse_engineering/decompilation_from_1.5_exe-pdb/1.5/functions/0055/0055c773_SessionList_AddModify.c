/*
 * Entry: 0055c773
 * Name: SessionList::AddModify
 * Namespace: SessionList
 * Signature: long AddModify(SessionList * this, dp_session_t * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __thiscall SessionList::AddModify(SessionList *this,dp_session_t *param_1)

{
  vector<Session_*,std::allocator<Session_*>_> *pvVar1;
  short sVar2;
  uchar uVar3;
  uchar uVar4;
  uchar uVar5;
  bool bVar6;
  char cVar7;
  Session **ppSVar8;
  Session *pSVar9;
  int iVar10;
  dp_session_t *pdVar11;
  Session *pSVar12;
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_> local_1c;
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_> local_14;
  SessionList *local_c;
  long local_8;
  
  local_c = this;
  local_8 = FindItemIndex(this,(param_1->field4_0xf).karma);
  pvVar1 = &this->sessionV;
  std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
            (&local_1c,(this->sessionV)._Myfirst,(_Container_base_aux *)pvVar1);
  local_14._padding_ = local_1c._padding_;
  local_14._Myptr = local_1c._Myptr;
  std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
            (&local_1c,(this->sessionV)._Mylast,(_Container_base_aux *)pvVar1);
  bVar6 = std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator==
                    (&local_14,&local_1c);
  do {
    if (bVar6) {
LAB_0055c844:
      std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
      _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
                (&local_1c,(this->sessionV)._Mylast,(_Container_base_aux *)&this->sessionV);
      bVar6 = std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator==
                        (&local_14,&local_1c);
      if (bVar6) {
        pSVar9 = operator_new(0x68);
        if (pSVar9 == (Session *)0x0) {
          param_1 = (dp_session_t *)0x0;
        }
        else {
          param_1 = &Session::Session(pSVar9,param_1)->dp_session;
        }
        std::vector<Session_*,std::allocator<Session_*>_>::push_back
                  (&this->sessionV,(Session **)&param_1);
        local_8 = (**(code **)(this->_padding_ + 0x10))(param_1);
      }
      return local_8;
    }
    ppSVar8 = std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator*
                        (&local_14);
    pSVar9 = *ppSVar8;
    sVar2 = (pSVar9->dp_session).field4_0xf.karma;
    if ((param_1->field4_0xf).karma == sVar2) {
      if (pSVar9->bBanned == false) {
        pSVar9->mark = 0x28;
        cVar7 = (**(code **)(this->_padding_ + 4))(pSVar9,param_1);
        if (cVar7 != '\0') {
          pdVar11 = param_1;
          pSVar12 = pSVar9;
          for (iVar10 = 0x17; iVar10 != 0; iVar10 = iVar10 + -1) {
            uVar3 = pdVar11->adrMaster[0];
            uVar4 = pdVar11->adrMaster[1];
            uVar5 = pdVar11->adrMaster[2];
            (pSVar12->dp_session).field0_0x0 = pdVar11->field0_0x0;
            (pSVar12->dp_session).adrMaster[0] = uVar3;
            (pSVar12->dp_session).adrMaster[1] = uVar4;
            (pSVar12->dp_session).adrMaster[2] = uVar5;
            pdVar11 = (dp_session_t *)(pdVar11->adrMaster + 3);
            pSVar12 = (Session *)((pSVar12->dp_session).adrMaster + 3);
          }
          uVar3 = pdVar11->adrMaster[0];
          (pSVar12->dp_session).field0_0x0 = pdVar11->field0_0x0;
          (pSVar12->dp_session).adrMaster[0] = uVar3;
          (pSVar12->dp_session).adrMaster[1] = pdVar11->adrMaster[1];
          local_8 = ModifyListItem(local_c,pSVar9);
          this = local_c;
        }
        goto LAB_0055c844;
      }
      DeleteListItem(this,sVar2);
    }
    std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator++(&local_14);
    std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
    _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
              (&local_1c,(this->sessionV)._Mylast,(_Container_base_aux *)pvVar1);
    bVar6 = std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator==
                      (&local_14,&local_1c);
  } while( true );
}
