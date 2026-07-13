/*
 * Entry: 0047cddd
 * Name: std::_Remove_copy<AnimSprite_*_*,std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*>
 * Namespace: std
 * Signature: _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> _Remove_copy<AnimSprite_*_*,std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*>(AnimSprite * * param_1, AnimSprite * * param_2, _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_3, AnimSprite * * param_4, _Range_checked_iterator_tag param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> __cdecl
std::
_Remove_copy<AnimSprite_*_*,std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*>
          (AnimSprite **param_1,AnimSprite **param_2,
          _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_3,AnimSprite **param_4,
          _Range_checked_iterator_tag param_5)

{
  AnimSprite **ppAVar1;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> _Var2;
  undefined3 in_stack_00000019;
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> local_c;
  
  for (; param_2 != (AnimSprite **)param_3._0_4_; param_2 = param_2 + 1) {
    if (*param_2 != (AnimSprite *)*_param_5) {
      local_c._padding_ = param_3._4_4_;
      local_c._Myptr = param_4;
      _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator++
                ((_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> *)
                 &param_3.field_0x4);
      ppAVar1 = _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator*
                          (&local_c);
      *ppAVar1 = *param_2;
      in_EDX = extraout_EDX;
    }
  }
  *param_1 = (AnimSprite *)param_3._4_4_;
  param_1[1] = (AnimSprite *)param_4;
  _Var2._4_4_ = in_EDX;
  _Var2._0_4_ = param_1;
  return _Var2;
}
