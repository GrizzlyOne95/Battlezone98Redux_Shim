/*
 * Entry: 004c8d98
 * Name: DisplayInterface::RemViewSimulate
 * Namespace: DisplayInterface
 * Signature: void RemViewSimulate(DisplayInterface * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DisplayInterface::RemViewSimulate(DisplayInterface *this,int param_1)

{
  list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *this_00;
  _Const_iterator<1> _Var1;
  _Iterator<1> _Var2;
  _Const_iterator<1> _Var3;
  _Iterator<1> _Var4;
  undefined1 local_24 [8];
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  this_00 = simulateList[param_1];
  std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
  _Const_iterator<1>(&local_1c,this_00->_Myhead,this_00);
  std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
  _Const_iterator<1>(&local_c,this_00->_Myhead,this_00);
  std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
  _Const_iterator<1>(&local_14,this_00->_Myhead->_Next,this_00);
  _Var4._4_4_ = local_14._padding_;
  _Var4._0_4_ = local_24;
  _Var2._4_4_ = local_c._padding_;
  _Var2._0_4_ = local_14._Ptr;
  _Var4 = std::
          remove_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
                    (_Var4,_Var2,(IsMyView)local_c._Ptr);
  _Var1._Ptr = (_Node *)*_Var4._0_4_;
  _Var1._padding_ = (int)&local_1c;
  _Var3._Ptr = (_Node *)local_1c._padding_;
  _Var3._padding_ = _Var4._0_4_[1];
  std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::erase(this_00,_Var1,_Var3);
  return;
}
