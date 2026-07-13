/*
 * Entry: 00467eae
 * Name: TurretAttack::CheckWaiting
 * Namespace: TurretAttack
 * Signature: bool CheckWaiting(TurretAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretAttack::CheckWaiting(TurretAttack *this)

{
  int iVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  AttackerInfo *pAVar5;
  GameObject *pGVar6;
  float *pfVar7;
  float *pfVar8;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  cVar3 = (**(code **)(*(int *)this->_padding_ + 100))();
  if (cVar3 == '\0') {
    iVar1 = this->_padding_;
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_c,(_Node *)**(undefined4 **)(iVar1 + 0x1c),
               (list<AttackerInfo,std::allocator<AttackerInfo>_> *)(iVar1 + 8));
    while( true ) {
      std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_14,*(_Node **)(iVar1 + 0x1c),
                 (list<AttackerInfo,std::allocator<AttackerInfo>_> *)(iVar1 + 8));
      bVar4 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator==
                        (&local_c,&local_14);
      if (bVar4) break;
      pAVar5 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator*
                         (&local_c);
      iVar2 = pAVar5->attackTask->curState;
      if (((iVar2 == 4) || (iVar2 == 0xc)) &&
         (pGVar6 = GameObjectHandle::GetObj(pAVar5->attackTask->himHandle),
         pGVar6 == (GameObject *)this->_padding_)) {
        pfVar7 = (float *)(**(code **)(pAVar5->attacker->_padding_ + 0xc))();
        pfVar8 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
        if (2500.0 <= (pfVar8[2] - pfVar7[2]) * (pfVar8[2] - pfVar7[2]) +
                      (*pfVar8 - *pfVar7) * (*pfVar8 - *pfVar7)) {
          return false;
        }
      }
      std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator++
                (&local_c);
    }
    this->_padding_ = 2;
    bVar4 = true;
  }
  else {
    bVar4 = false;
  }
  return bVar4;
}
