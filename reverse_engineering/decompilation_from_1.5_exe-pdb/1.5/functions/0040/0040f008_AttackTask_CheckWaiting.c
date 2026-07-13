/*
 * Entry: 0040f008
 * Name: AttackTask::CheckWaiting
 * Namespace: AttackTask
 * Signature: bool CheckWaiting(AttackTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AttackTask::CheckWaiting(AttackTask *this)

{
  int iVar1;
  bool bVar2;
  AttackerInfo *pAVar3;
  GameObject *pGVar4;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  iVar1 = this->_padding_;
  std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,(_Node *)**(undefined4 **)(iVar1 + 0x1c),
             (list<AttackerInfo,std::allocator<AttackerInfo>_> *)(iVar1 + 8));
  while( true ) {
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,*(_Node **)(iVar1 + 0x1c),
               (list<AttackerInfo,std::allocator<AttackerInfo>_> *)(iVar1 + 8));
    bVar2 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar2) {
      this->_padding_ = 2;
      return true;
    }
    pAVar3 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator*
                       (&local_c);
    if ((pAVar3->attackTask->curState == 0xc) &&
       (pGVar4 = GameObjectHandle::GetObj(pAVar3->attackTask->himHandle),
       pGVar4 == (GameObject *)this->_padding_)) break;
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator++(&local_c);
  }
  return false;
}
