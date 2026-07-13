/*
 * Entry: 0055c948
 * Name: PlayerList::Enum
 * Namespace: PlayerList
 * Signature: void Enum(PlayerList * this, dp_playerId_t * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::Enum(PlayerList *this,dp_playerId_t *param_1)

{
  vector<Player_*,std::allocator<Player_*>_> *pvVar1;
  dp_playerId_t *pdVar2;
  bool bVar3;
  char cVar4;
  Player **ppPVar5;
  Player *pPVar6;
  char *pcVar7;
  uchar *puVar8;
  int iVar9;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_18;
  _Vector_const_iterator<Player_*,std::allocator<Player_*>_> local_10;
  PlayerList *local_8;
  
  pvVar1 = &this->playerV;
  local_8 = this;
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
  pdVar2 = param_1;
  do {
    if (bVar3) {
LAB_0055ca18:
      std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
      _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
                (&local_18,(local_8->playerV)._Mylast,(_Container_base_aux *)&local_8->playerV);
      bVar3 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                        (&local_10,&local_18);
      if (bVar3) {
        pPVar6 = operator_new(0x4c);
        if (pPVar6 == (Player *)0x0) {
          param_1 = (dp_playerId_t *)0x0;
        }
        else {
          param_1 = (dp_playerId_t *)Player::Player(pPVar6,pdVar2->name,(pdVar2->field0_0x0).id);
        }
        pcVar7 = pdVar2->name;
        iVar9 = (int)param_1 - (int)pcVar7;
        do {
          cVar4 = *pcVar7;
          pcVar7[iVar9] = cVar4;
          pcVar7 = pcVar7 + 1;
        } while (cVar4 != '\0');
        puVar8 = param_1->blob + 9;
        puVar8[0] = '\0';
        puVar8[1] = '\0';
        puVar8[2] = '\0';
        puVar8[3] = '\0';
        *(undefined4 *)(param_1->blob + 0xd) = 0;
        *(undefined4 *)((int)&param_1[1].field0_0x0 + 1) = 0;
        param_1[1].adr[1] = '\0';
        param_1[1].adr[2] = '\0';
        param_1[1].adr[3] = '\0';
        param_1[1].adr[4] = '\0';
        memcpy(puVar8,pdVar2->blob,pdVar2->bloblen);
        std::vector<Player_*,std::allocator<Player_*>_>::push_back
                  (&local_8->playerV,(Player **)&param_1);
        AddListItem(local_8,pdVar2);
      }
      return;
    }
    ppPVar5 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator*(&local_10);
    pPVar6 = *ppPVar5;
    if ((pdVar2->field0_0x0).id == pPVar6->id) {
      pPVar6->mark = 1;
      cVar4 = (**(code **)(local_8->_padding_ + 4))(pPVar6,pdVar2);
      if (cVar4 != '\0') {
        pcVar7 = pdVar2->name;
        iVar9 = (int)pPVar6 - (int)pcVar7;
        do {
          cVar4 = *pcVar7;
          pcVar7[iVar9] = cVar4;
          pcVar7 = pcVar7 + 1;
        } while (cVar4 != '\0');
        pcVar7 = pPVar6->blob;
        pcVar7[0] = '\0';
        pcVar7[1] = '\0';
        pcVar7[2] = '\0';
        pcVar7[3] = '\0';
        pPVar6->blob[4] = '\0';
        pPVar6->blob[5] = '\0';
        pPVar6->blob[6] = '\0';
        pPVar6->blob[7] = '\0';
        pPVar6->blob[8] = '\0';
        pPVar6->blob[9] = '\0';
        pPVar6->blob[10] = '\0';
        pPVar6->blob[0xb] = '\0';
        pPVar6->blob[0xc] = '\0';
        pPVar6->blob[0xd] = '\0';
        pPVar6->blob[0xe] = '\0';
        pPVar6->blob[0xf] = '\0';
        memcpy(pcVar7,pdVar2->blob,pdVar2->bloblen);
        ModifyListItem(local_8,pPVar6);
      }
      goto LAB_0055ca18;
    }
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator++(&local_10);
    std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::
    _Vector_const_iterator<Player_*,std::allocator<Player_*>_>
              (&local_18,(this->playerV)._Mylast,(_Container_base_aux *)pvVar1);
    bVar3 = std::_Vector_const_iterator<Player_*,std::allocator<Player_*>_>::operator==
                      (&local_10,&local_18);
  } while( true );
}
