/*
 * Entry: 00402b80
 * Name: AiMission::Create
 * Namespace: AiMission
 * Signature: AiMission * Create(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __cdecl AiMission::Create(char *param_1)

{
  AiMissionClass *pAVar1;
  bool bVar2;
  AiMissionClass **ppAVar3;
  int iVar4;
  int iVar5;
  AiMission *pAVar6;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  pAVar6 = (AiMission *)0x0;
  iVar5 = 0;
  do {
    if (pAVar6 != (AiMission *)0x0) {
      current = pAVar6;
      return pAVar6;
    }
    std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&local_c,missions->_Myhead->_Next,missions);
    while( true ) {
      std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Const_iterator<1>::
      _Const_iterator<1>(&local_14,missions->_Myhead,missions);
      bVar2 = std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Const_iterator<1>::
              operator==(&local_c,&local_14);
      if (bVar2) break;
      ppAVar3 = std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Const_iterator<1>::
                operator*(&local_c);
      pAVar1 = *ppAVar3;
      iVar4 = (**(code **)pAVar1->_padding_)(param_1);
      if (iVar4 != 0) {
        pAVar6 = (AiMission *)(**(code **)(pAVar1->_padding_ + 4))();
        break;
      }
      std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Const_iterator<1>::operator++
                (&local_c);
    }
    iVar5 = iVar5 + 1;
    param_1 = "empty";
    if (1 < iVar5) {
      current = pAVar6;
      return pAVar6;
    }
  } while( true );
}
