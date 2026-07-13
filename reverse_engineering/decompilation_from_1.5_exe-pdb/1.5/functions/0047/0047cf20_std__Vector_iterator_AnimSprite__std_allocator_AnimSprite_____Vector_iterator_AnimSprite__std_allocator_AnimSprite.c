/*
 * Entry: 0047cf20
 * Name: std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Namespace: std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> * _Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>(_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> * this, AnimSprite * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> * __thiscall
std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::
_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
          (_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> *this,AnimSprite **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
            ((_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> *)this,param_1,
             param_2);
  return this;
}
