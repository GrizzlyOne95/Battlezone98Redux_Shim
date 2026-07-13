/*
 * Entry: 00403744
 * Name: AiPath::SaveAll
 * Namespace: AiPath
 * Signature: bool SaveAll(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl AiPath::SaveAll(_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  AiPath **ppAVar3;
  _Const_iterator<1> local_18;
  _Const_iterator<1> local_10;
  int local_8;
  
  bVar1 = ::out(param_1,"[AiPaths]");
  if (bVar1) {
    local_8 = 0;
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_10,(pathList._Myhead)->_Next,&pathList);
    while( true ) {
      std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_18,pathList._Myhead,&pathList);
      bVar1 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator==
                        (&local_10,&local_18);
      if (bVar1) break;
      ppAVar3 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator*
                          (&local_10);
      if ((*ppAVar3)->bDontSave == false) {
        local_8 = local_8 + 1;
      }
      std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator++(&local_10);
    }
    bVar1 = ::out(param_1,&local_8,4,"count");
    if (bVar1) {
      std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_10,(pathList._Myhead)->_Next,&pathList);
      bVar1 = true;
      do {
        std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
                  (&local_18,pathList._Myhead,&pathList);
        bVar2 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator==
                          (&local_10,&local_18);
        if (bVar2) {
          return bVar1;
        }
        ppAVar3 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator*
                            (&local_10);
        if ((*ppAVar3)->bDontSave == false) {
          bVar1 = Save(*ppAVar3,param_1);
        }
        std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator++(&local_10);
      } while (bVar1 != false);
    }
  }
  return false;
}
