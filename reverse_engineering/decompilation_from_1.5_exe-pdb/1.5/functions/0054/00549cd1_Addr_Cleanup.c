/*
 * Entry: 00549cd1
 * Name: Addr::Cleanup
 * Namespace: Addr
 * Signature: void Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Addr::Cleanup(void)

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
      if (pAVar1->pointer != (void *)0x0) {
        pvVar4 = OldNew::Find(pAVar1->pointer);
        *pAVar1->address = pvVar4;
      }
      operator_delete(pAVar1);
      std::list<Addr_*,std::allocator<Addr_*>_>::_Const_iterator<1>::operator++(&local_c);
      std::list<Addr_*,std::allocator<Addr_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_14,table->_Myhead,table);
      bVar2 = std::list<Addr_*,std::allocator<Addr_*>_>::_Const_iterator<1>::operator==
                        (&local_c,&local_14);
    }
    if (table != (list<Addr_*,std::allocator<Addr_*>_> *)0x0) {
      std::list<Addr_*,std::allocator<Addr_*>_>::_scalar_deleting_destructor_(table,1);
    }
    table = (list<Addr_*,std::allocator<Addr_*>_> *)0x0;
    OldNew::Cleanup();
  }
  return;
}
