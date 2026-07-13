/*
 * Entry: 0047cfe4
 * Name: stdext::unchecked_remove_copy<std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*>
 * Namespace: stdext
 * Signature: _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> unchecked_remove_copy<std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*>(_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_1, _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_2, _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_3, AnimSprite * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> __cdecl
stdext::
unchecked_remove_copy<std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*>
          (_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_1,
          _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_2,
          _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> param_3,AnimSprite **param_4)

{
  _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> _Var1;
  _Range_checked_iterator_tag in_stack_00000020;
  
  _Var1 = std::
          _Remove_copy<AnimSprite_*_*,std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*>
                    ((AnimSprite **)param_1._0_4_,(AnimSprite **)param_2._0_4_,param_3,param_4,
                     in_stack_00000020);
  _Var1._0_4_ = param_1._0_4_;
  return _Var1;
}
