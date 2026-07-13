/*
 * Entry: 0040eab6
 * Name: AttackGroup::Find
 * Namespace: AttackGroup
 * Signature: AttackGroup * Find(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AttackGroup * __cdecl AttackGroup::Find(GameObject *param_1)

{
  bool bVar1;
  AttackGroup **ppAVar2;
  GameObject *pGVar3;
  AttackGroup *pAVar4;
  int iVar5;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,(attackGroups._Myhead)->_Next,&attackGroups);
  while( true ) {
    std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,attackGroups._Myhead,&attackGroups);
    bVar1 = std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar1) {
      pAVar4 = operator_new(0x24);
      if (pAVar4 == (AttackGroup *)0x0) {
        pAVar4 = (AttackGroup *)0x0;
      }
      else {
        std::list<AttackerInfo,std::allocator<AttackerInfo>_>::
        list<AttackerInfo,std::allocator<AttackerInfo>_>(&pAVar4->attackers);
      }
      local_c._Ptr = (_Node *)pAVar4;
      if (param_1 == (GameObject *)0x0) {
        iVar5 = 0;
      }
      else {
        iVar5 = GameObject::GetHandle(param_1);
      }
      pAVar4->target = iVar5;
      std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::push_back
                (&attackGroups,(AttackGroup **)&local_c._Ptr);
      return pAVar4;
    }
    ppAVar2 = std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Const_iterator<1>::operator*
                        (&local_c);
    pGVar3 = GameObjectHandle::GetObj((*ppAVar2)->target);
    if (pGVar3 == param_1) break;
    std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Const_iterator<1>::operator++
              (&local_c);
  }
  ppAVar2 = std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Const_iterator<1>::operator*
                      (&local_c);
  return *ppAVar2;
}
