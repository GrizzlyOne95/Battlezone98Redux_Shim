/*
 * Entry: 004c8abd
 * Name: DisplayInterface::DisplayInterface
 * Namespace: DisplayInterface
 * Signature: DisplayInterface * DisplayInterface(DisplayInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DisplayInterface * __thiscall DisplayInterface::DisplayInterface(DisplayInterface *this)

{
  list<DisplayInterface_*,std::allocator<DisplayInterface_*>_> *this_00;
  list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *plVar1;
  int iVar2;
  bool bVar3;
  DisplayInterface *local_8;
  
  this->diName = (char *)0x0;
  bVar3 = done == 0;
  this->_padding_ = (int)&_vftable_;
  if (bVar3) {
    local_8 = this;
    this_00 = operator_new(0x1c);
    if (this_00 == (list<DisplayInterface_*,std::allocator<DisplayInterface_*>_> *)0x0) {
      displayList = (list<DisplayInterface_*,std::allocator<DisplayInterface_*>_> *)0x0;
    }
    else {
      displayList = std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::
                    list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>(this_00);
    }
    iVar2 = 0;
    do {
      plVar1 = operator_new(0x1c);
      if (plVar1 == (list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *)0x0) {
        plVar1 = (list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *)0x0;
      }
      else {
        plVar1 = std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::
                 list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>(plVar1);
      }
      *(list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> **)((int)simulateList + iVar2) =
           plVar1;
      plVar1 = operator_new(0x1c);
      if (plVar1 == (list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *)0x0) {
        plVar1 = (list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *)0x0;
      }
      else {
        plVar1 = std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::
                 list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>(plVar1);
      }
      *(list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> **)((int)renderList + iVar2) =
           plVar1;
      iVar2 = iVar2 + 4;
    } while (iVar2 < 0x30);
    done = 1;
  }
  local_8 = this;
  std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::push_back(displayList,&local_8)
  ;
  return this;
}
