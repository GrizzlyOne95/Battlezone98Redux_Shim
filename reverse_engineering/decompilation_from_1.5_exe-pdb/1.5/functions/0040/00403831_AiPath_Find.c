/*
 * Entry: 00403831
 * Name: AiPath::Find
 * Namespace: AiPath
 * Signature: AiPath * Find(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiPath * __cdecl AiPath::Find(char *param_1)

{
  byte bVar1;
  bool bVar2;
  byte *pbVar3;
  int iVar4;
  AiPath **ppAVar5;
  byte *pbVar6;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,(pathList._Myhead)->_Next,&pathList);
  local_c._padding_ = local_14._padding_;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,pathList._Myhead,&pathList);
    bVar2 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar2) break;
    ppAVar5 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator*(&local_c)
    ;
    pbVar3 = (byte *)(*ppAVar5)->label;
    pbVar6 = (byte *)param_1;
    if (pbVar3 != (byte *)0x0) {
      do {
        bVar1 = *pbVar3;
        bVar2 = bVar1 < *pbVar6;
        if (bVar1 != *pbVar6) {
LAB_0040388c:
          iVar4 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
          goto LAB_00403891;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar2 = bVar1 < pbVar6[1];
        if (bVar1 != pbVar6[1]) goto LAB_0040388c;
        pbVar3 = pbVar3 + 2;
        pbVar6 = pbVar6 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_00403891:
      if (iVar4 == 0) break;
    }
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator++(&local_c);
  }
  std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,pathList._Myhead,&pathList);
  bVar2 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator==
                    (&local_c,&local_14);
  if (!bVar2) {
    ppAVar5 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator*(&local_c)
    ;
    return *ppAVar5;
  }
  return (AiPath *)0x0;
}
