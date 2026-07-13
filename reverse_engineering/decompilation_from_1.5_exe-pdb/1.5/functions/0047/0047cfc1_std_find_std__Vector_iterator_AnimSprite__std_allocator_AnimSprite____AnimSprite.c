/*
 * Entry: 0047cfc1
 * Name: std::find<std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*>
 * Namespace: std
 * Signature: _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> find<std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*>(_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_1, _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_2, AnimSprite * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> __cdecl
std::find<std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*>
          (_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_1,
          _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_2,AnimSprite **param_3)

{
  AnimSprite **ppAVar1;
  AnimSprite **in_stack_00000018;
  
  ppAVar1 = _Find<AnimSprite_*_*,AnimSprite_*>
                      ((AnimSprite **)param_2._0_4_,param_3,in_stack_00000018);
  *(undefined4 *)param_1._0_4_ = param_1._4_4_;
  *(AnimSprite ***)(param_1._0_4_ + 4) = ppAVar1;
  return param_1;
}
