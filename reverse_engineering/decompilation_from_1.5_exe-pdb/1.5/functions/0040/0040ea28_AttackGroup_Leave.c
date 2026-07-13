/*
 * Entry: 0040ea28
 * Name: AttackGroup::Leave
 * Namespace: AttackGroup
 * Signature: void Leave(AttackGroup * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AttackGroup::Leave(AttackGroup *this,GameObject *param_1)

{
  list<AttackerInfo,std::allocator<AttackerInfo>_> *this_00;
  _Const_iterator<1> _Var1;
  bool bVar2;
  AttackerInfo *pAVar3;
  _Node *p_Var4;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  this_00 = &this->attackers;
  std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,((this->attackers)._Myhead)->_Next,this_00);
  local_c._padding_ = local_14._padding_;
  p_Var4 = (this->attackers)._Myhead;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,p_Var4,this_00);
    bVar2 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar2) break;
    pAVar3 = std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator*
                       (&local_c);
    if (pAVar3->attacker == param_1) break;
    std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Const_iterator<1>::operator++(&local_c);
    p_Var4 = (this->attackers)._Myhead;
  }
  _Var1._Ptr = (_Node *)local_c._padding_;
  _Var1._padding_ = (int)&local_14;
  std::list<AttackerInfo,std::allocator<AttackerInfo>_>::erase(this_00,_Var1);
  if ((this->attackers)._Mysize == 0) {
    param_1 = (GameObject *)this;
    std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::remove
              (&attackGroups,(AttackGroup **)&param_1);
  }
  return;
}
