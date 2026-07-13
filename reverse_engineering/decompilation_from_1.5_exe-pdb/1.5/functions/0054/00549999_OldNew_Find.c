/*
 * Entry: 00549999
 * Name: OldNew::Find
 * Namespace: OldNew
 * Signature: void * Find(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl OldNew::Find(void *param_1)

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
    if (bVar1) {
      return (void *)0x0;
    }
    ppOVar2 = std::list<OldNew_*,std::allocator<OldNew_*>_>::_Const_iterator<1>::operator*(&local_c)
    ;
    if ((*ppOVar2)->old_pointer == param_1) break;
    std::list<OldNew_*,std::allocator<OldNew_*>_>::_Const_iterator<1>::operator++(&local_c);
  }
  return (*ppOVar2)->new_pointer;
}
