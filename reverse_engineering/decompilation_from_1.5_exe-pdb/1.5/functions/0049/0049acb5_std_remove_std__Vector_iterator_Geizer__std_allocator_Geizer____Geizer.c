/*
 * Entry: 0049acb5
 * Name: std::remove<std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*>
 * Namespace: std
 * Signature: _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> remove<std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*>(_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> param_1, _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> param_2, Geizer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> __cdecl
std::remove<std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*>
          (_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> param_1,
          _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> param_2,Geizer **param_3)

{
  _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var1;
  _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var2;
  undefined4 uVar3;
  bool bVar4;
  undefined4 extraout_EDX;
  _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var5;
  _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var6;
  _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> _Var7;
  Geizer **in_stack_00000018;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_c;
  
  uVar3 = param_1._4_4_;
  local_c._Myptr = (Geizer **)param_2._0_4_;
  param_2._0_4_ = _Find<Geizer_*_*,Geizer_*>((Geizer **)param_2._0_4_,param_3,in_stack_00000018);
  param_1._4_4_ = uVar3;
  bVar4 = _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator==
                    ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)
                     &param_1.field_0x4,
                     (_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)
                     &param_2.field_0x4);
  if (bVar4) {
    *(undefined4 *)param_1._0_4_ = param_1._4_4_;
    *(undefined4 *)(param_1._0_4_ + 4) = param_2._0_4_;
    _Var5._4_4_ = extraout_EDX;
    _Var5._0_4_ = param_1._0_4_;
    return _Var5;
  }
  local_c._padding_ = param_1._4_4_;
  local_c._Myptr = (Geizer **)param_2._0_4_;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator++(&local_c);
  _Var6._4_4_ = local_c._padding_;
  _Var6._0_4_ = param_1._0_4_;
  _Var1._4_4_ = param_2._4_4_;
  _Var1._0_4_ = local_c._Myptr;
  _Var2._4_4_ = param_1._4_4_;
  _Var2._0_4_ = param_3;
  _Var6 = stdext::
          unchecked_remove_copy<std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>,Geizer_*>
                    (_Var6,_Var1,_Var2,(Geizer **)param_2._0_4_);
  _Var7._4_4_ = _Var6._4_4_;
  _Var7._0_4_ = param_1._0_4_;
  return _Var7;
}
