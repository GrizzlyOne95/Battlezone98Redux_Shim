/*
 * Entry: 00412152
 * Name: FollowGroup::GetSlot
 * Namespace: FollowGroup
 * Signature: int GetSlot(FollowGroup * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall FollowGroup::GetSlot(FollowGroup *this,GameObject *param_1)

{
  bool bVar1;
  FollowerInfo *pFVar2;
  int iVar3;
  _Node *p_Var4;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  iVar3 = 0;
  std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,((this->followers)._Myhead)->_Next,&this->followers);
  local_c._padding_ = local_14._padding_;
  p_Var4 = (this->followers)._Myhead;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,p_Var4,&this->followers);
    bVar1 = std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar1) {
      return iVar3;
    }
    pFVar2 = std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator*
                       (&local_c);
    if (pFVar2->follower == param_1) break;
    iVar3 = iVar3 + 1;
    std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator++(&local_c);
    p_Var4 = (this->followers)._Myhead;
  }
  return iVar3;
}
