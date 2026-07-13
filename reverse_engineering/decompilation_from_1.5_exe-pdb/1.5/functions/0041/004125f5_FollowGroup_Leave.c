/*
 * Entry: 004125f5
 * Name: FollowGroup::Leave
 * Namespace: FollowGroup
 * Signature: void Leave(FollowGroup * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FollowGroup::Leave(FollowGroup *this,GameObject *param_1)

{
  list<FollowerInfo,std::allocator<FollowerInfo>_> *this_00;
  _Const_iterator<1> _Var1;
  bool bVar2;
  FollowerInfo *pFVar3;
  _Node *p_Var4;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  this_00 = &this->followers;
  std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,((this->followers)._Myhead)->_Next,this_00);
  local_c._padding_ = local_14._padding_;
  p_Var4 = (this->followers)._Myhead;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,p_Var4,this_00);
    bVar2 = std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar2) break;
    pFVar3 = std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator*
                       (&local_c);
    if (pFVar3->follower == param_1) break;
    std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator++(&local_c);
    p_Var4 = (this->followers)._Myhead;
  }
  _Var1._Ptr = (_Node *)local_c._padding_;
  _Var1._padding_ = (int)&local_14;
  std::list<FollowerInfo,std::allocator<FollowerInfo>_>::erase(this_00,_Var1);
  std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,((this->followers)._Myhead)->_Next,this_00);
  local_c._padding_ = local_14._padding_;
  p_Var4 = (this->followers)._Myhead;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,p_Var4,this_00);
    bVar2 = std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar2) break;
    pFVar3 = std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator*
                       (&local_c);
    pFVar3->needsReset = true;
    std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator++(&local_c);
    p_Var4 = (this->followers)._Myhead;
  }
  if ((this->followers)._Mysize == 0) {
    param_1 = (GameObject *)this;
    std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::remove
              (&followGroups,(FollowGroup **)&param_1);
    ~FollowGroup(this);
    operator_delete(this);
  }
  return;
}
