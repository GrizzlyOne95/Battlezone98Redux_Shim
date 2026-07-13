/*
 * Entry: 004c8127
 * Name: std::_Remove_copy_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>,std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
 * Namespace: std
 * Signature: _Iterator<1> _Remove_copy_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>,std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>(_Iterator<0> param_1, _Iterator<0> param_2, _Iterator<1> param_3, IsMyView param_4, _Range_checked_iterator_tag param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __cdecl
std::
_Remove_copy_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>,std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
          (_Iterator<0> param_1,_Iterator<0> param_2,_Iterator<1> param_3,IsMyView param_4,
          _Range_checked_iterator_tag param_5)

{
  DisplayViewInfo **ppDVar1;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  _Iterator<1> _Var2;
  undefined3 in_stack_00000021;
  _Const_iterator<1> local_c;
  
  for (; param_2._0_4_ != param_3._0_4_; param_2._0_4_ = *(undefined4 *)param_2._0_4_) {
    if (*(int *)(*(int *)(param_2._0_4_ + 8) + 4) != _param_5) {
      local_c._padding_ = param_3._4_4_;
      local_c._Ptr = (_Node *)param_4.me;
      list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::operator++
                ((_Const_iterator<1> *)&param_3.field_0x4);
      ppDVar1 = list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
                operator*(&local_c);
      *ppDVar1 = *(DisplayViewInfo **)(param_2._0_4_ + 8);
      in_EDX = extraout_EDX;
    }
  }
  *(undefined4 *)param_1._0_4_ = param_3._4_4_;
  *(DisplayInterface **)(param_1._0_4_ + 4) = param_4.me;
  _Var2._4_4_ = in_EDX;
  _Var2._0_4_ = param_1._0_4_;
  return _Var2;
}
