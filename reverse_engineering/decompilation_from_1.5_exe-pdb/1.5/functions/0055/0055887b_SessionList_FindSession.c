/*
 * Entry: 0055887b
 * Name: SessionList::FindSession
 * Namespace: SessionList
 * Signature: Session * FindSession(SessionList * this, short param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Session * __thiscall SessionList::FindSession(SessionList *this,short param_1)

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
    if (bVar1) {
      return (Session *)0x0;
    }
    ppSVar2 = std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator*(&local_c)
    ;
    if (param_1 == ((*ppSVar2)->dp_session).field4_0xf.karma) break;
    std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator++(&local_c);
    ppSVar2 = (this->sessionV)._Mylast;
  }
  return *ppSVar2;
}
