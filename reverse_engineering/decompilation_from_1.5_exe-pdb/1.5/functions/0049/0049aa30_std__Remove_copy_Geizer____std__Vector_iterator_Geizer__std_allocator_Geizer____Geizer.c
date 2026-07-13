/*
 * Entry: 0049aa30
 * Name: std::_Remove_copy<Geizer_*_*,std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*>
 * Namespace: std
 * Signature: _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Remove_copy<Geizer_*_*,std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*>(Geizer * * param_1, Geizer * * param_2, _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> param_3, Geizer * * param_4, _Range_checked_iterator_tag param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> __cdecl
std::_Remove_copy<Geizer_*_*,std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*>
          (Geizer **param_1,Geizer **param_2,
          _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> param_3,Geizer **param_4,
          _Range_checked_iterator_tag param_5)

{
  Geizer **ppGVar1;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var2;
  undefined3 in_stack_00000019;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_c;
  
  for (; param_2 != (Geizer **)param_3._0_4_; param_2 = param_2 + 1) {
    if (*param_2 != (Geizer *)*_param_5) {
      local_c._padding_ = param_3._4_4_;
      local_c._Myptr = param_4;
      _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator++
                ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)&param_3.field_0x4);
      ppGVar1 = _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator*(&local_c);
      *ppGVar1 = *param_2;
      in_EDX = extraout_EDX;
    }
  }
  *param_1 = (Geizer *)param_3._4_4_;
  param_1[1] = (Geizer *)param_4;
  _Var2._4_4_ = in_EDX;
  _Var2._0_4_ = param_1;
  return _Var2;
}
