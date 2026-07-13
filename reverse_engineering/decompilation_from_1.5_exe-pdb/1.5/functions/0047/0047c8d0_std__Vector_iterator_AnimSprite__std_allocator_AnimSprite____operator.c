/*
 * Entry: 0047c8d0
 * Name: std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator++
 * Namespace: std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> * operator++(_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> * __thiscall
std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator++
          (_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> *this)

{
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator++
            ((_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> *)this);
  return this;
}
