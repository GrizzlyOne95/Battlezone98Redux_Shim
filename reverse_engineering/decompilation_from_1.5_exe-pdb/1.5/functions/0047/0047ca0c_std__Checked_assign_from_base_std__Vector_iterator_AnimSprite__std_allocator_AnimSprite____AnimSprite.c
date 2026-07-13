/*
 * Entry: 0047ca0c
 * Name: std::_Checked_assign_from_base<std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*_*>
 * Namespace: std
 * Signature: void _Checked_assign_from_base<std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*_*>(_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> * param_1, AnimSprite * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Checked_assign_from_base<std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>,AnimSprite_*_*>
          (_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> *param_1,
          AnimSprite ***param_2)

{
  *(AnimSprite ***)&param_1->field_0x4 = *param_2;
  return;
}
