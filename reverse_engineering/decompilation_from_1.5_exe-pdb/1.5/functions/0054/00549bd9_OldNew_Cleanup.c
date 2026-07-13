/*
 * Entry: 00549bd9
 * Name: OldNew::Cleanup
 * Namespace: OldNew
 * Signature: void Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl OldNew::Cleanup(void)

{
  bool bVar1;
  OldNew **ppOVar2;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<OldNew_*,std::allocator<OldNew_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,otable->_Myhead->_Next,otable);
  while( true ) {
    std::list<OldNew_*,std::allocator<OldNew_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,otable->_Myhead,otable);
    bVar1 = std::list<OldNew_*,std::allocator<OldNew_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar1) break;
    ppOVar2 = std::list<OldNew_*,std::allocator<OldNew_*>_>::_Const_iterator<1>::operator*(&local_c)
    ;
    if (*ppOVar2 != (OldNew *)0x0) {
      operator_delete(*ppOVar2);
    }
    std::list<OldNew_*,std::allocator<OldNew_*>_>::_Const_iterator<1>::operator++(&local_c);
  }
  if (otable != (list<OldNew_*,std::allocator<OldNew_*>_> *)0x0) {
    std::list<OldNew_*,std::allocator<OldNew_*>_>::_scalar_deleting_destructor_(otable,1);
  }
  otable = (list<OldNew_*,std::allocator<OldNew_*>_> *)0x0;
  return;
}
