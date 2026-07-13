/*
 * Entry: 0055b5c8
 * Name: GameSessionList::EndEnum
 * Namespace: GameSessionList
 * Signature: void EndEnum(GameSessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameSessionList::EndEnum(GameSessionList *this)

{
  undefined1 *this_00;
  Session *pSVar1;
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_> _Var2;
  bool bVar3;
  Session **ppSVar4;
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_> local_14;
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_> local_c;
  
  this_00 = &this->field_0x14;
  std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
            (&local_14,*(Session ***)&this->field_0x20,(_Container_base_aux *)this_00);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
            (&local_14,*(Session ***)&this->field_0x24,(_Container_base_aux *)this_00);
  bVar3 = std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator==
                    (&local_c,&local_14);
  while( true ) {
    if (bVar3) {
      return;
    }
    ppSVar4 = std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator*(&local_c)
    ;
    pSVar1 = *ppSVar4;
    if (pSVar1->mark < 0) break;
    std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator++(&local_c);
    std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
    _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
              (&local_14,*(Session ***)&this->field_0x24,(_Container_base_aux *)this_00);
    bVar3 = std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator==
                      (&local_c,&local_14);
  }
  SessionList::DeleteListItem((SessionList *)this,(pSVar1->dp_session).field4_0xf.karma);
  operator_delete(pSVar1);
  _Var2._Myptr = (Session **)local_c._padding_;
  _Var2._padding_ = (int)&local_14;
  std::vector<Session_*,std::allocator<Session_*>_>::erase
            ((vector<Session_*,std::allocator<Session_*>_> *)this_00,_Var2);
  return;
}
