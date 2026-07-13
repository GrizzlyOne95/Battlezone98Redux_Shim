/*
 * Entry: 0047ca44
 * Name: stdext::unchecked_uninitialized_copy<AnimSprite_*_*,AnimSprite_*_*,std::allocator<AnimSprite_*>_>
 * Namespace: stdext
 * Signature: AnimSprite * * unchecked_uninitialized_copy<AnimSprite_*_*,AnimSprite_*_*,std::allocator<AnimSprite_*>_>(AnimSprite * * param_1, AnimSprite * * param_2, AnimSprite * * param_3, allocator<AnimSprite_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimSprite ** __cdecl
stdext::unchecked_uninitialized_copy<AnimSprite_*_*,AnimSprite_*_*,std::allocator<AnimSprite_*>_>
          (AnimSprite **param_1,AnimSprite **param_2,AnimSprite **param_3,
          allocator<AnimSprite_*> *param_4)

{
  AnimSprite **ppAVar1;
  
  ppAVar1 = std::_Uninit_copy<AnimSprite_*_*,AnimSprite_*_*,std::allocator<AnimSprite_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppAVar1;
}
