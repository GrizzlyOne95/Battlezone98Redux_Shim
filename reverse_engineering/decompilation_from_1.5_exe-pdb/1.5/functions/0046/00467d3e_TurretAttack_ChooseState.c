/*
 * Entry: 00467d3e
 * Name: TurretAttack::ChooseState
 * Namespace: TurretAttack
 * Signature: void ChooseState(TurretAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretAttack::ChooseState(TurretAttack *this)

{
  float fVar1;
  bool bVar2;
  GameObject *pGVar3;
  float *pfVar4;
  float *pfVar5;
  int iVar6;
  list<AttackerInfo,std::allocator<AttackerInfo>_> *plVar7;
  _Const_iterator<1> local_20;
  _Const_iterator<1> local_18;
  AttackerInfo *local_10;
  GameObject *local_c;
  float local_8;
  
  pGVar3 = GameObjectHandle::GetObj(this->_padding_);
  this->_padding_ = (int)pGVar3;
  if (pGVar3 == (GameObject *)0x0) {
    this->_padding_ = 0xd;
    return;
  }
  pfVar4 = (float *)(**(code **)(pGVar3->_padding_ + 0xc))();
  pfVar5 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
  if (this->attackRangeSq <=
      (pfVar5[2] - pfVar4[2]) * (pfVar5[2] - pfVar4[2]) + (*pfVar5 - *pfVar4) * (*pfVar5 - *pfVar4))
  {
    iVar6 = this->_padding_;
    local_8 = 1e+30;
    local_c = (GameObject *)0x0;
    plVar7 = (list<AttackerInfo,std::allocator<AttackerInfo>_> *)(iVar6 + 8);
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_18,(_Node *)**(undefined4 **)(iVar6 + 0x1c),plVar7);
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_20,*(_Node **)(iVar6 + 0x1c),plVar7);
    bVar2 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator==
                      (&local_18,&local_20);
    if (!bVar2) {
      do {
        local_10 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::
                   operator*(&local_18);
        if ((local_10->attacker != (GameObject *)this->_padding_) &&
           ((local_10->attackTask->curState == 0xb || (local_10->attackTask->nextState == 0xb)))) {
          pfVar4 = (float *)(**(code **)(local_10->attacker->_padding_ + 0xc))();
          pfVar5 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
          fVar1 = (pfVar5[2] - pfVar4[2]) * (pfVar5[2] - pfVar4[2]) +
                  (*pfVar5 - *pfVar4) * (*pfVar5 - *pfVar4);
          if ((fVar1 <= 22500.0) && (fVar1 <= local_8)) {
            local_c = local_10->attacker;
            local_8 = fVar1;
          }
        }
        std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator++
                  (&local_18);
        std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::
        _Const_iterator<1>(&local_20,*(_Node **)(iVar6 + 0x1c),plVar7);
        bVar2 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::
                operator==(&local_18,&local_20);
      } while (!bVar2);
      if (local_c != (GameObject *)0x0) {
        iVar6 = GameObject::GetHandle(local_c);
        this->_padding_ = 4;
        goto LAB_00467ea7;
      }
    }
    this->_padding_ = 0xb;
  }
  else {
    this->_padding_ = 5;
  }
  iVar6 = this->_padding_;
LAB_00467ea7:
  this->_padding_ = iVar6;
  return;
}
