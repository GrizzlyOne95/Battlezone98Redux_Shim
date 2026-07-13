/*
 * Entry: 004123f0
 * Name: FollowGroup::Join
 * Namespace: FollowGroup
 * Signature: void Join(FollowGroup * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FollowGroup::Join(FollowGroup *this,GameObject *param_1)

{
  list<FollowerInfo,std::allocator<FollowerInfo>_> *this_00;
  bool bVar1;
  FollowerInfo *pFVar2;
  _Node *p_Var3;
  undefined8 local_14;
  _Const_iterator<1> local_c;
  
  this_00 = &this->followers;
  std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,((this->followers)._Myhead)->_Next,this_00);
  p_Var3 = (this->followers)._Myhead;
  while( true ) {
    std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
              ((_Const_iterator<1> *)&local_14,p_Var3,this_00);
    bVar1 = std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator==
                      (&local_c,(_Const_iterator<1> *)&local_14);
    if (bVar1) break;
    pFVar2 = std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator*
                       (&local_c);
    pFVar2->needsReset = true;
    std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::operator++(&local_c);
    p_Var3 = (this->followers)._Myhead;
  }
  local_14._0_4_ = param_1;
  local_14._4_1_ = true;
  std::list<FollowerInfo,std::allocator<FollowerInfo>_>::push_back
            (this_00,(FollowerInfo *)&local_14);
  return;
}
