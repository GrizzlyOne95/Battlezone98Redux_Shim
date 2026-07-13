/*
 * Entry: 004c86e8
 * Name: DisplayInterface_Init
 * Namespace: Global
 * Signature: void DisplayInterface_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisplayInterface_Init(void)

{
  bool bVar1;
  DisplayInterface **ppDVar2;
  _Const_iterator<1> _Stack_14;
  _Const_iterator<1> _Stack_c;
  
  DisplayInterface::cursorIndex = 0;
  DisplayInterface::textFont = Default_Font;
  DisplayInterface::textLeft = 0x14;
  DisplayInterface::textTop = 0x14;
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
    (**(code **)((*ppDVar2)->_padding_ + 4))();
    std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::_Const_iterator<1>::
    operator++(&_Stack_c);
  }
  reg_add_ent_func(DisplayInterface::DI_AddEntity);
  reg_del_ent_func(DisplayInterface::DI_DeleteEntity);
  return;
}
