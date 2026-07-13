/*
 * Entry: 004c8633
 * Name: DisplayInterface::RenderAll
 * Namespace: DisplayInterface
 * Signature: void RenderAll(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisplayInterface::RenderAll(int param_1)

{
  list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *plVar1;
  bool bVar2;
  DisplayViewInfo **ppDVar3;
  _Const_iterator<1> local_18;
  _Const_iterator<1> local_10;
  float local_8;
  
  if (useDisplayInterface != 0) {
    local_8 = spriteZ;
    plVar1 = renderList[param_1];
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&local_18,plVar1->_Myhead->_Next,plVar1);
    local_10._padding_ = local_18._padding_;
    local_10._Ptr = local_18._Ptr;
    while( true ) {
      std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
      _Const_iterator<1>(&local_18,plVar1->_Myhead,plVar1);
      bVar2 = std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
              operator==(&local_10,&local_18);
      if (bVar2) break;
      ppDVar3 = std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>
                ::operator*(&local_10);
      (**(code **)((*ppDVar3)->display->_padding_ + 0x18))();
      spriteZ = local_8;
      std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
      operator++(&local_10);
    }
    if (0 < cursorIndex) {
      DrawSprite(currentBuffer,cursorIndex,mousePos.x,mousePos.y,0x250001);
      cursorIndex = 0;
    }
  }
  return;
}
