/*
 * Entry: 004c8bda
 * Name: stdext::unchecked_remove_copy_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
 * Namespace: stdext
 * Signature: _Iterator<1> unchecked_remove_copy_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>(_Iterator<1> param_1, _Iterator<1> param_2, _Iterator<1> param_3, IsMyView param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __cdecl
stdext::
unchecked_remove_copy_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
          (_Iterator<1> param_1,_Iterator<1> param_2,_Iterator<1> param_3,IsMyView param_4)

{
  _Iterator<0> _Var1;
  _Iterator<0> _Var2;
  _Iterator<1> _Var3;
  _Iterator<1> _Var4;
  _Range_checked_iterator_tag in_stack_00000020;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::
  _Checked_iterator_base((_Iterator<1> *)&param_2.field_0x4);
  std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::
  _Checked_iterator_base((_Iterator<1> *)&param_1.field_0x4);
  _Var1._4_4_ = local_18;
  _Var1._0_4_ = param_1._0_4_;
  _Var2._4_4_ = local_10;
  _Var2._0_4_ = local_14;
  _Var3._4_4_ = param_3._4_4_;
  _Var3._0_4_ = local_c;
  _Var3 = std::
          _Remove_copy_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>,std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
                    (_Var1,_Var2,_Var3,param_4,in_stack_00000020);
  _Var4._4_4_ = _Var3._4_4_;
  _Var4._0_4_ = param_1._0_4_;
  return _Var4;
}
