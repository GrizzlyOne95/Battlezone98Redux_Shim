/*
 * Entry: 0040b571
 * Name: AOI::Find
 * Namespace: AOI
 * Signature: AOI * Find(AiPath * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AOI * __cdecl AOI::Find(AiPath *param_1)

{
  bool bVar1;
  AOI **ppAVar2;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,(areas._Myhead)->_Next,&areas);
  while( true ) {
    std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,areas._Myhead,&areas);
    bVar1 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar1) {
      return (AOI *)0x0;
    }
    ppAVar2 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator*(&local_c);
    if ((*ppAVar2)->path == param_1) break;
    std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator++(&local_c);
  }
  return *ppAVar2;
}
