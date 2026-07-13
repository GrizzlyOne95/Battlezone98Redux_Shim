/*
 * Entry: 0047d48d
 * Name: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Umove<AnimSprite_*_*>
 * Namespace: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: AnimSprite * * _Umove<AnimSprite_*_*>(vector<AnimSprite_*,std::allocator<AnimSprite_*>_> * this, AnimSprite * * param_1, AnimSprite * * param_2, AnimSprite * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimSprite ** __thiscall
std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Umove<AnimSprite_*_*>
          (vector<AnimSprite_*,std::allocator<AnimSprite_*>_> *this,AnimSprite **param_1,
          AnimSprite **param_2,AnimSprite **param_3)

{
  AnimSprite **ppAVar1;
  
  ppAVar1 = stdext::
            unchecked_uninitialized_copy<AnimSprite_*_*,AnimSprite_*_*,std::allocator<AnimSprite_*>_>
                      (param_1,param_2,param_3,(allocator<AnimSprite_*> *)&this->_padding_);
  return ppAVar1;
}
