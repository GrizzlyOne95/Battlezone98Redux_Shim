/*
 * Entry: 0040e654
 * Name: AttackGroup::GetSlot
 * Namespace: AttackGroup
 * Signature: int GetSlot(AttackGroup * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall AttackGroup::GetSlot(AttackGroup *this,GameObject *param_1)

{
  bool bVar1;
  AttackerInfo *pAVar2;
  int iVar3;
  _Node *p_Var4;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  iVar3 = 0;
  std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,((this->attackers)._Myhead)->_Next,&this->attackers);
  local_c._padding_ = local_14._padding_;
  p_Var4 = (this->attackers)._Myhead;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,p_Var4,&this->attackers);
    bVar1 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar1) {
      return iVar3;
    }
    pAVar2 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator*
                       (&local_c);
    if (pAVar2->attacker == param_1) break;
    iVar3 = iVar3 + 1;
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator++(&local_c);
    p_Var4 = (this->attackers)._Myhead;
  }
  return iVar3;
}
