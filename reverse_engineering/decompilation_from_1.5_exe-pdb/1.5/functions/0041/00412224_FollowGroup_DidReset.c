/*
 * Entry: 00412224
 * Name: FollowGroup::DidReset
 * Namespace: FollowGroup
 * Signature: void DidReset(FollowGroup * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FollowGroup::DidReset(FollowGroup *this,GameObject *param_1)

{
  bool bVar1;
  FollowerInfo *pFVar2;
  _Node *p_Var3;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,((this->followers)._Myhead)->_Next,&this->followers);
  local_c._padding_ = local_14._padding_;
  p_Var3 = (this->followers)._Myhead;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,p_Var3,&this->followers);
    bVar1 = std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar1) {
      return;
    }
    pFVar2 = std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator*
                       (&local_c);
    if (pFVar2->follower == param_1) break;
    std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator++(&local_c);
    p_Var3 = (this->followers)._Myhead;
  }
  pFVar2->needsReset = false;
  return;
}
