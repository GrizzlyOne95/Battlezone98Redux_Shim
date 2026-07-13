/*
 * Entry: 0047ce68
 * Name: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::~vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Namespace: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: void ~vector<AnimSprite_*,std::allocator<AnimSprite_*>_>(vector<AnimSprite_*,std::allocator<AnimSprite_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::
~vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
          (vector<AnimSprite_*,std::allocator<AnimSprite_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
