/*
 * Entry: 004af33e
 * Name: std::_Remove_copy<Scrap_*_*,std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*>
 * Namespace: std
 * Signature: _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> _Remove_copy<Scrap_*_*,std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*>(Scrap * * param_1, Scrap * * param_2, _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_3, Scrap * * param_4, _Range_checked_iterator_tag param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> __cdecl
std::_Remove_copy<Scrap_*_*,std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*>
          (Scrap **param_1,Scrap **param_2,
          _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_3,Scrap **param_4,
          _Range_checked_iterator_tag param_5)

{
  Scrap **ppSVar1;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> _Var2;
  undefined3 in_stack_00000019;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> local_c;
  
  for (; param_2 != (Scrap **)param_3._0_4_; param_2 = param_2 + 1) {
    if (*param_2 != (Scrap *)*_param_5) {
      local_c._padding_ = param_3._4_4_;
      local_c._Myptr = param_4;
      _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator++
                ((_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> *)&param_3.field_0x4);
      ppSVar1 = _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator*(&local_c);
      *ppSVar1 = *param_2;
      in_EDX = extraout_EDX;
    }
  }
  *param_1 = (Scrap *)param_3._4_4_;
  param_1[1] = (Scrap *)param_4;
  _Var2._4_4_ = in_EDX;
  _Var2._0_4_ = param_1;
  return _Var2;
}
