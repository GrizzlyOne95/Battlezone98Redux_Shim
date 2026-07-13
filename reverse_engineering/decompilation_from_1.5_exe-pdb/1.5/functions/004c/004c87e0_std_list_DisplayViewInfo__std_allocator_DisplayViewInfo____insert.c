/*
 * Entry: 004c87e0
 * Name: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::insert
 * Namespace: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>
 * Signature: _Iterator<1> insert(list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> * this, _Const_iterator<1> param_1, DisplayViewInfo * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::insert
          (list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *this,
          _Const_iterator<1> param_1,DisplayViewInfo **param_2)

{
  _Const_iterator<1> _Var1;
  _Const_iterator<1> *p_Var2;
  undefined4 extraout_EDX;
  _Iterator<1> _Var3;
  DisplayViewInfo **in_stack_00000010;
  
  _Var1._Ptr = (_Node *)param_2;
  _Var1._padding_ = (int)param_1._Ptr;
  _Insert(this,_Var1,in_stack_00000010);
  p_Var2 = _Const_iterator<1>::operator--((_Const_iterator<1> *)&param_1._Ptr);
  _Const_iterator<1>::_Const_iterator<1>((_Const_iterator<1> *)param_1._padding_,p_Var2->_Ptr,this);
  _Var3._4_4_ = extraout_EDX;
  _Var3._0_4_ = param_1._padding_;
  return _Var3;
}
