/*
 * Entry: 0041254d
 * Name: FollowGroup::Find
 * Namespace: FollowGroup
 * Signature: FollowGroup * Find(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FollowGroup * __cdecl FollowGroup::Find(GameObject *param_1)

{
  bool bVar1;
  FollowGroup **ppFVar2;
  GameObject *pGVar3;
  FollowGroup *pFVar4;
  int iVar5;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,(followGroups._Myhead)->_Next,&followGroups);
  while( true ) {
    std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,followGroups._Myhead,&followGroups);
    bVar1 = std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar1) {
      pFVar4 = operator_new(0x20);
      if (pFVar4 == (FollowGroup *)0x0) {
        pFVar4 = (FollowGroup *)0x0;
      }
      else {
        std::list<FollowerInfo,std::allocator<FollowerInfo>_>::
        list<FollowerInfo,std::allocator<FollowerInfo>_>(&pFVar4->followers);
      }
      local_c._Ptr = (_Node *)pFVar4;
      if (param_1 == (GameObject *)0x0) {
        iVar5 = 0;
      }
      else {
        iVar5 = GameObject::GetHandle(param_1);
      }
      pFVar4->leader = iVar5;
      std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::push_back
                (&followGroups,(FollowGroup **)&local_c._Ptr);
      return pFVar4;
    }
    ppFVar2 = std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Const_iterator<1>::operator*
                        (&local_c);
    pGVar3 = GameObjectHandle::GetObj((*ppFVar2)->leader);
    if (pGVar3 == param_1) break;
    std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Const_iterator<1>::operator++
              (&local_c);
  }
  ppFVar2 = std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::_Const_iterator<1>::operator*
                      (&local_c);
  return *ppFVar2;
}
