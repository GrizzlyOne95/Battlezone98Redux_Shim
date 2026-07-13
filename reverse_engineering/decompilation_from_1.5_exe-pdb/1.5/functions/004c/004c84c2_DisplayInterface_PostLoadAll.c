/*
 * Entry: 004c84c2
 * Name: DisplayInterface::PostLoadAll
 * Namespace: DisplayInterface
 * Signature: void PostLoadAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisplayInterface::PostLoadAll(void)

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
    (**(code **)((*ppDVar2)->_padding_ + 0x10))();
    std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::
    operator++(&local_c);
  }
  return;
}
