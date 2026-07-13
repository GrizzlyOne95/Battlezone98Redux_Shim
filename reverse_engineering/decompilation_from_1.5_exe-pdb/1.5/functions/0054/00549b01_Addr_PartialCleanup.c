/*
 * Entry: 00549b01
 * Name: Addr::PartialCleanup
 * Namespace: Addr
 * Signature: void PartialCleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Addr::PartialCleanup(void)

{
  Addr *pAVar1;
  bool bVar2;
  Addr **ppAVar3;
  void *pvVar4;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  if (table != (list<Addr_*,std::allocator<Addr_*>_> *)0x0) {
    std::list<Addr_*,std::allocator<Addr_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_c,table->_Myhead->_Next,table);
    std::list<Addr_*,std::allocator<Addr_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,table->_Myhead,table);
    bVar2 = std::list<Addr_*,std::allocator<Addr_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    while (!bVar2) {
      ppAVar3 = std::list<Addr_*,std::allocator<Addr_*>_>::_Const_iterator<1>::operator*(&local_c);
      pAVar1 = *ppAVar3;
      pvVar4 = pAVar1->pointer;
      if ((pvVar4 != (void *)0x0) && (pvVar4 = OldNew::Find(pvVar4), pvVar4 != (void *)0x0)) {
        *pAVar1->address = pvVar4;
      }
      std::list<Addr_*,std::allocator<Addr_*>_>::_Const_iterator<1>::operator++(&local_c);
      std::list<Addr_*,std::allocator<Addr_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_14,table->_Myhead,table);
      bVar2 = std::list<Addr_*,std::allocator<Addr_*>_>::_Const_iterator<1>::operator==
                        (&local_c,&local_14);
    }
  }
  return;
}
