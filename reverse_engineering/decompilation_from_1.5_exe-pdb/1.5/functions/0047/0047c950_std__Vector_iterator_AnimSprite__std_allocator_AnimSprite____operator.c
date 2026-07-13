/*
 * Entry: 0047c950
 * Name: std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator+=
 * Namespace: std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> * operator+=(_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> * __thiscall
std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator+=
          (_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> *this,int param_1)

{
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator+=
            ((_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> *)this,param_1);
  return this;
}
