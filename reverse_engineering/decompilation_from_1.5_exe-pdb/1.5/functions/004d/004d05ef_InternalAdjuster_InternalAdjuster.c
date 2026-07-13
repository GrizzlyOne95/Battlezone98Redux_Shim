/*
 * Entry: 004d05ef
 * Name: InternalAdjuster::InternalAdjuster
 * Namespace: InternalAdjuster
 * Signature: InternalAdjuster * InternalAdjuster(InternalAdjuster * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

InternalAdjuster * __thiscall InternalAdjuster::InternalAdjuster(InternalAdjuster *this)

{
  int *this_00;
  list<AdjustItem_*,std::allocator<AdjustItem_*>_> *this_01;
  _Const_iterator<1> local_c;
  
  this_00 = &this->_padding_;
  this->_padding_ = (int)&AdjustVar::_vftable_;
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  DisplayInterface::DisplayInterface((DisplayInterface *)this_00);
  this_01 = &this->adjustList;
  this->_padding_ = (int)&_vftable__for__AdjustVar__;
  *this_00 = (int)&_vftable__for__DisplayInterface__;
  std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::
  list<AdjustItem_*,std::allocator<AdjustItem_*>_>(this_01);
  *(undefined4 *)&this->curAdjItem = 0;
  *(undefined4 *)&(this->curAdjItem).field_0x4 = 0;
  local_c._Ptr = operator_new(8);
  if (local_c._Ptr == (_Node *)0x0) {
    local_c._Ptr = (_Node *)0x0;
  }
  else {
    (local_c._Ptr)->_Next = (_Node *)&AiTaskAdjItem::_vftable_;
    (local_c._Ptr)->_Prev = (_Node *)0xd;
  }
  std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::push_back
            (this_01,(AdjustItem **)&local_c._Ptr);
  local_c._Ptr = operator_new(8);
  if (local_c._Ptr == (_Node *)0x0) {
    local_c._Ptr = (_Node *)0x0;
  }
  else {
    (local_c._Ptr)->_Next = (_Node *)&TimeAdjItem::_vftable_;
    *(undefined1 *)&(local_c._Ptr)->_Prev = 0;
  }
  std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::push_back
            (this_01,(AdjustItem **)&local_c._Ptr);
  std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,(this->adjustList)._Myhead,this_01);
  *(int *)&this->curAdjItem = local_c._padding_;
  *(_Node **)&(this->curAdjItem).field_0x4 = local_c._Ptr;
  DisplayInterface::AddView((DisplayInterface *)this_00,0,5);
  DisplayInterface::AddView((DisplayInterface *)this_00,9,5);
  AdjustVar::Set((AdjustVar *)this);
  return this;
}
