/*
 * Entry: 0040e6bd
 * Name: AttackGroup::GetLeft
 * Namespace: AttackGroup
 * Signature: AttackerInfo * GetLeft(AttackGroup * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AttackerInfo * __thiscall AttackGroup::GetLeft(AttackGroup *this,GameObject *param_1)

{
  list<AttackerInfo,std::allocator<AttackerInfo>_> *plVar1;
  bool bVar2;
  AttackerInfo *pAVar3;
  _Node *p_Var4;
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  plVar1 = &this->attackers;
  std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,(this->attackers)._Myhead,plVar1);
  std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_1c,((this->attackers)._Myhead)->_Next,plVar1);
  local_c._padding_ = local_1c._padding_;
  p_Var4 = (this->attackers)._Myhead;
  local_c._Ptr = local_1c._Ptr;
  while( true ) {
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_1c,p_Var4,plVar1);
    bVar2 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_1c);
    if (bVar2) {
      return (AttackerInfo *)0x0;
    }
    pAVar3 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator*
                       (&local_c);
    if (pAVar3->attacker == param_1) break;
    local_14._padding_ = local_c._padding_;
    local_14._Ptr = local_c._Ptr;
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator++(&local_c);
    p_Var4 = (this->attackers)._Myhead;
  }
  std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_1c,(this->attackers)._Myhead,plVar1);
  bVar2 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator==
                    (&local_14,&local_1c);
  if (bVar2) {
    return (AttackerInfo *)0x0;
  }
  pAVar3 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator*
                     (&local_14);
  return pAVar3;
}
