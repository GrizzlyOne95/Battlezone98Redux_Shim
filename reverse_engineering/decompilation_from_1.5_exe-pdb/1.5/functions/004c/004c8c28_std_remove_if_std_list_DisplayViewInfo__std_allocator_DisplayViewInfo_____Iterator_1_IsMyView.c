/*
 * Entry: 004c8c28
 * Name: std::remove_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
 * Namespace: std
 * Signature: _Iterator<1> remove_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>(_Iterator<1> param_1, _Iterator<1> param_2, IsMyView param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __cdecl
std::
remove_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
          (_Iterator<1> param_1,_Iterator<1> param_2,IsMyView param_3)

{
  _Iterator<1> _Var1;
  _Iterator<1> _Var2;
  _Iterator<1> _Var3;
  bool bVar4;
  undefined4 extraout_EDX;
  _Iterator<1> _Var5;
  _Iterator<1> _Var6;
  _Iterator<1> _Var7;
  _Const_iterator<1> local_c;
  
  _Var5._4_4_ = param_1._4_4_;
  _Var5._0_4_ = &local_c;
  _Var5 = find_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
                    (_Var5,param_2,param_3);
  param_1._4_4_ = *_Var5._0_4_;
  param_2._0_4_ = _Var5._0_4_[1];
  bVar4 = list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::operator==
                    ((_Const_iterator<1> *)&param_1.field_0x4,
                     (_Const_iterator<1> *)&param_2.field_0x4);
  if (bVar4) {
    *(undefined4 *)param_1._0_4_ = param_1._4_4_;
    *(undefined4 *)(param_1._0_4_ + 4) = param_2._0_4_;
    _Var6._4_4_ = extraout_EDX;
    _Var6._0_4_ = param_1._0_4_;
    return _Var6;
  }
  local_c._padding_ = param_1._4_4_;
  local_c._Ptr = (_Node *)param_2._0_4_;
  list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::operator++
            (&local_c);
  _Var1._4_4_ = local_c._padding_;
  _Var1._0_4_ = param_1._0_4_;
  _Var2._4_4_ = param_2._4_4_;
  _Var2._0_4_ = local_c._Ptr;
  _Var3._4_4_ = param_1._4_4_;
  _Var3._0_4_ = param_3.me;
  _Var5 = stdext::
          unchecked_remove_copy_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
                    (_Var1,_Var2,_Var3,(IsMyView)param_2._0_4_);
  _Var7._4_4_ = _Var5._4_4_;
  _Var7._0_4_ = param_1._0_4_;
  return _Var7;
}
