/*
 * Entry: 0047d597
 * Name: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Ufill
 * Namespace: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: AnimSprite * * _Ufill(vector<AnimSprite_*,std::allocator<AnimSprite_*>_> * this, AnimSprite * * param_1, uint param_2, AnimSprite * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimSprite ** __thiscall
std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Ufill
          (vector<AnimSprite_*,std::allocator<AnimSprite_*>_> *this,AnimSprite **param_1,
          uint param_2,AnimSprite **param_3)

{
  stdext::unchecked_fill_n<AnimSprite_*_*,unsigned_int,AnimSprite_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
