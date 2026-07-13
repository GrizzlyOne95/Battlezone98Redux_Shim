/*
 * Entry: 004c86ed
 * Name: DisplayInterface_PostLoad
 * Namespace: Global
 * Signature: void DisplayInterface_PostLoad(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisplayInterface_PostLoad(void)

{
  bool bVar1;
  DisplayInterface **ppDVar2;
  _Const_iterator<1> _Stack_14;
  _Const_iterator<1> _Stack_c;
  
  std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::
  _Const_iterator<1>(&_Stack_14,displayList->_Myhead->_Next,displayList);
  _Stack_c._padding_ = _Stack_14._padding_;
  _Stack_c._Ptr = _Stack_14._Ptr;
  while( true ) {
    std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&_Stack_14,displayList->_Myhead,displayList);
    bVar1 = std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::
            operator==(&_Stack_c,&_Stack_14);
    if (bVar1) break;
    ppDVar2 = std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>
              ::operator*(&_Stack_c);
    (**(code **)((*ppDVar2)->_padding_ + 0x10))();
    std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::
    operator++(&_Stack_c);
  }
  return;
}
