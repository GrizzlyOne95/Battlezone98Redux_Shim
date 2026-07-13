/*
 * Entry: 004c8b84
 * Name: std::find_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
 * Namespace: std
 * Signature: _Iterator<1> find_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>(_Iterator<1> param_1, _Iterator<1> param_2, IsMyView param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __cdecl
std::find_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
          (_Iterator<1> param_1,_Iterator<1> param_2,IsMyView param_3)

{
  _Iterator<0> _Var1;
  undefined4 extraout_EDX;
  _Iterator<0> _Var2;
  _Iterator<1> _Var3;
  undefined1 local_1c [8];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  IsMyView local_8;
  
  list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::_Checked_iterator_base
            ((_Iterator<1> *)&param_2.field_0x4);
  list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::_Checked_iterator_base
            ((_Iterator<1> *)&param_1.field_0x4);
  _Var2._4_4_ = local_14;
  _Var2._0_4_ = local_1c;
  _Var1._4_4_ = local_c;
  _Var1._0_4_ = local_10;
  _Var2 = _Find_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<0>,IsMyView>
                    (_Var2,_Var1,local_8);
  list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>::
  _Checked_iterator_assign_from_base((_Iterator<1> *)&param_1.field_0x4,*_Var2._0_4_);
  *(undefined4 *)param_1._0_4_ = param_1._4_4_;
  *(undefined4 *)(param_1._0_4_ + 4) = param_2._0_4_;
  _Var3._4_4_ = extraout_EDX;
  _Var3._0_4_ = param_1._0_4_;
  return _Var3;
}
