/*
 * Entry: 004c8584
 * Name: DisplayInterface::SimulateAll
 * Namespace: DisplayInterface
 * Signature: void SimulateAll(int param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisplayInterface::SimulateAll(int param_1,float param_2)

{
  list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *plVar1;
  bool bVar2;
  DisplayViewInfo **ppDVar3;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  currentBuffer = View_Record.MainCam.Buffer;
  currentCamera = &View_Record.MainCam;
  mousePos.x = ((((View_Record.MainCam.Buffer)->Pane).x1 - ((View_Record.MainCam.Buffer)->Pane).x0)
               + 1) * command_controls.cmd_x >> 0x10;
  plVar1 = simulateList[param_1];
  mousePos.y = ((((View_Record.MainCam.Buffer)->Pane).y1 - ((View_Record.MainCam.Buffer)->Pane).y0)
               + 1) * command_controls.cmd_y >> 0x10;
  std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
  _Const_iterator<1>(&local_14,plVar1->_Myhead->_Next,plVar1);
  local_c._padding_ = local_14._padding_;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&local_14,plVar1->_Myhead,plVar1);
    bVar2 = std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
            operator==(&local_c,&local_14);
    if (bVar2) break;
    ppDVar3 = std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
              operator*(&local_c);
    (**(code **)((*ppDVar3)->display->_padding_ + 0x14))(param_2);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::operator++
              (&local_c);
  }
  return;
}
