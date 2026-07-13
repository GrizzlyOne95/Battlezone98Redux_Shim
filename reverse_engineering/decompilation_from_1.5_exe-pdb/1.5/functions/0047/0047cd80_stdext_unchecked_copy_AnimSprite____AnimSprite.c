/*
 * Entry: 0047cd80
 * Name: stdext::unchecked_copy<AnimSprite_*_*,AnimSprite_*_*>
 * Namespace: stdext
 * Signature: AnimSprite * * unchecked_copy<AnimSprite_*_*,AnimSprite_*_*>(AnimSprite * * param_1, AnimSprite * * param_2, AnimSprite * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimSprite ** __cdecl
stdext::unchecked_copy<AnimSprite_*_*,AnimSprite_*_*>
          (AnimSprite **param_1,AnimSprite **param_2,AnimSprite **param_3)

{
  AnimSprite **ppAVar1;
  
  ppAVar1 = std::_Copy_opt<AnimSprite_*_*,AnimSprite_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Scalar_ptr_iterator_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppAVar1;
}
