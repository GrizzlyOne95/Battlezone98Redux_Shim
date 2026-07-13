/*
 * Entry: 005586fd
 * Name: ServerList::StartEnum
 * Namespace: ServerList
 * Signature: void StartEnum(ServerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ServerList::StartEnum(ServerList *this)

{
  bool bVar1;
  Server **ppSVar2;
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> local_14;
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_> local_c;
  
  std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
            (&local_14,(this->serverV)._Myfirst,(_Container_base_aux *)&this->serverV);
  local_c._padding_ = local_14._padding_;
  ppSVar2 = (this->serverV)._Mylast;
  local_c._Myptr = local_14._Myptr;
  while( true ) {
    std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::
    _Vector_const_iterator<Server_*,std::allocator<Server_*>_>
              (&local_14,ppSVar2,(_Container_base_aux *)&this->serverV);
    bVar1 = std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar1) break;
    ppSVar2 = std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator*(&local_c);
    (*ppSVar2)->mark = (*ppSVar2)->mark + -1;
    std::_Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator++(&local_c);
    ppSVar2 = (this->serverV)._Mylast;
  }
  this->bInEnumServers = true;
  this->bEnumed = false;
  return;
}
