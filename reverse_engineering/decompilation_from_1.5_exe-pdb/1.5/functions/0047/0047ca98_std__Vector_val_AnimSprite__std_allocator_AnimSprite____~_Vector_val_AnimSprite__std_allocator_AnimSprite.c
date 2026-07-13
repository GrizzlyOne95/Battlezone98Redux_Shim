/*
 * Entry: 0047ca98
 * Name: std::_Vector_val<AnimSprite_*,std::allocator<AnimSprite_*>_>::~_Vector_val<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Namespace: std::_Vector_val<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: void ~_Vector_val<AnimSprite_*,std::allocator<AnimSprite_*>_>(_Vector_val<AnimSprite_*,std::allocator<AnimSprite_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<AnimSprite_*,std::allocator<AnimSprite_*>_>::
~_Vector_val<AnimSprite_*,std::allocator<AnimSprite_*>_>
          (_Vector_val<AnimSprite_*,std::allocator<AnimSprite_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
