/*
 * Entry: 004c83c8
 * Name: DisplayInterface::DI_DeleteEntity
 * Namespace: DisplayInterface
 * Signature: void DI_DeleteEntity(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisplayInterface::DI_DeleteEntity(tagENTITY *param_1)

{
  bool bVar1;
  DisplayInterface **ppDVar2;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
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
    (**(code **)((*ppDVar2)->_padding_ + 0xc))(param_1);
    std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::
    operator++(&local_c);
  }
  return;
}
