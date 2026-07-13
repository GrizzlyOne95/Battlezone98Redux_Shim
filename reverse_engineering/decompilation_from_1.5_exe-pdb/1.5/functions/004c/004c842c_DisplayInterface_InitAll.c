/*
 * Entry: 004c842c
 * Name: DisplayInterface::InitAll
 * Namespace: DisplayInterface
 * Signature: void InitAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisplayInterface::InitAll(void)

{
  bool bVar1;
  DisplayInterface **ppDVar2;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  cursorIndex = 0;
  textFont = Default_Font;
  textLeft = 0x14;
  textTop = 0x14;
  std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::
  _Const_iterator<1>(&local_14,displayList->_Myhead->_Next,displayList);
  local_c._padding_ = local_14._padding_;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&local_14,displayList->_Myhead,displayList);
    bVar1 = std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::
            operator==(&local_c,&local_14);
    if (bVar1) break;
    ppDVar2 = std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>
              ::operator*(&local_c);
    (**(code **)((*ppDVar2)->_padding_ + 4))();
    std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::
    operator++(&local_c);
  }
  reg_add_ent_func(DI_AddEntity);
  reg_del_ent_func(DI_DeleteEntity);
  return;
}
