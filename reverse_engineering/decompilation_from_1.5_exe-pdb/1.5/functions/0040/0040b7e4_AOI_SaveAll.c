/*
 * Entry: 0040b7e4
 * Name: AOI::SaveAll
 * Namespace: AOI
 * Signature: bool SaveAll(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl AOI::SaveAll(_iobuf *param_1)

{
  bool bVar1;
  AOI **ppAVar2;
  _Const_iterator<1> local_18;
  _Const_iterator<1> local_10;
  int local_8;
  
  bVar1 = ::out(param_1,"[AOIs]");
  if (bVar1) {
    local_8 = 0;
    std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_10,(areas._Myhead)->_Next,&areas);
    while( true ) {
      std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_18,areas._Myhead,&areas);
      bVar1 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator==
                        (&local_10,&local_18);
      if (bVar1) break;
      ppAVar2 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator*(&local_10);
      if ((*ppAVar2)->bDontSave == false) {
        local_8 = local_8 + 1;
      }
      std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator++(&local_10);
    }
    bVar1 = ::out(param_1,&local_8,4,"size");
    if (bVar1) {
      std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_10,(areas._Myhead)->_Next,&areas);
      do {
        std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::_Const_iterator<1>
                  (&local_18,areas._Myhead,&areas);
        bVar1 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator==
                          (&local_10,&local_18);
        if (bVar1) {
          return true;
        }
        ppAVar2 = std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator*(&local_10);
        bVar1 = Save(*ppAVar2,param_1);
        std::list<AOI_*,std::allocator<AOI_*>_>::_Const_iterator<1>::operator++(&local_10);
      } while (bVar1);
    }
  }
  return false;
}
