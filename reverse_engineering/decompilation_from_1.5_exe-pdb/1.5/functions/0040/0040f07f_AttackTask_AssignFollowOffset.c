/*
 * Entry: 0040f07f
 * Name: AttackTask::AssignFollowOffset
 * Namespace: AttackTask
 * Signature: void AssignFollowOffset(AttackTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AttackTask::AssignFollowOffset(AttackTask *this)

{
  int *piVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  AttackerInfo *pAVar6;
  GameObject *pGVar7;
  list<AttackerInfo,std::allocator<AttackerInfo>_> *plVar8;
  _Const_iterator<1> local_20;
  _Const_iterator<1> local_18;
  GameObject *local_10;
  uint local_c;
  uint local_8;
  
  local_10 = GameObjectHandle::GetObj(this->_padding_);
  if (local_10 == (GameObject *)0x0) {
    this->_padding_ = 0x40400000;
    fVar2 = -30.0;
  }
  else {
    local_8 = 0;
    local_c = 0xffffffff;
    iVar3 = this->_padding_;
    plVar8 = (list<AttackerInfo,std::allocator<AttackerInfo>_> *)(iVar3 + 8);
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_18,(_Node *)**(undefined4 **)(iVar3 + 0x1c),plVar8);
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_20,*(_Node **)(iVar3 + 0x1c),plVar8);
    bVar5 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator==
                      (&local_18,&local_20);
    if (!bVar5) {
      do {
        pAVar6 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::
                 operator*(&local_18);
        iVar4 = pAVar6->attackTask->curState;
        if ((2 < iVar4) &&
           (((iVar4 < 5 || (iVar4 == 0xc)) &&
            (pGVar7 = GameObjectHandle::GetObj(pAVar6->attackTask->himHandle), pGVar7 == local_10)))
           ) {
          if (pAVar6->attacker == (GameObject *)this->_padding_) {
            local_c = local_8;
          }
          local_8 = local_8 + 1;
        }
        std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator++
                  (&local_18);
        std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::
        _Const_iterator<1>(&local_20,*(_Node **)(iVar3 + 0x1c),plVar8);
        bVar5 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::
                operator==(&local_18,&local_20);
      } while (!bVar5);
      if (4 < local_8) {
        this->_padding_ = 0;
        fVar2 = (float)(int)(local_c + 1) * -20.0;
        goto LAB_0040f18a;
      }
    }
    piVar1 = (int *)((int)(&offsets4[3].z)[local_8] + local_c * 8);
    this->_padding_ = *piVar1;
    fVar2 = (float)piVar1[1];
  }
LAB_0040f18a:
  this->_padding_ = (int)fVar2;
  return;
}
