/*
 * Entry: 005588e2
 * Name: SessionList::StartEnum
 * Namespace: SessionList
 * Signature: void StartEnum(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SessionList::StartEnum(SessionList *this)

{
  bool bVar1;
  Session **ppSVar2;
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_> local_14;
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_> local_c;
  
  std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
            (&local_14,(this->sessionV)._Myfirst,(_Container_base_aux *)&this->sessionV);
  local_c._padding_ = local_14._padding_;
  ppSVar2 = (this->sessionV)._Mylast;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
    _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
              (&local_14,ppSVar2,(_Container_base_aux *)&this->sessionV);
    bVar1 = std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar1) break;
    ppSVar2 = std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator*(&local_c)
    ;
    (*ppSVar2)->mark = (*ppSVar2)->mark + -1;
    std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator++(&local_c);
    ppSVar2 = (this->sessionV)._Mylast;
  }
  this->dp_karma_found = 0;
  this->optFoundNumber = 0x7fff;
  this->bFoundSes = false;
  return;
}
