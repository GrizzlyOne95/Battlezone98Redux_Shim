/*
 * Entry: 0047c816
 * Name: std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Checked_iterator_assign_from_base
 * Namespace: std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: void _Checked_iterator_assign_from_base(_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> * this, AnimSprite * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::
_Checked_iterator_assign_from_base
          (_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> *this,AnimSprite **param_1)

{
  *(AnimSprite ***)&this->field_0x4 = param_1;
  return;
}
