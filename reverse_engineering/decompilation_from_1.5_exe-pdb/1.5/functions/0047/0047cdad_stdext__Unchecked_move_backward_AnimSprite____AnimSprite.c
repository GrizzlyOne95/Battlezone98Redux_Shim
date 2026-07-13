/*
 * Entry: 0047cdad
 * Name: stdext::_Unchecked_move_backward<AnimSprite_*_*,AnimSprite_*_*>
 * Namespace: stdext
 * Signature: AnimSprite * * _Unchecked_move_backward<AnimSprite_*_*,AnimSprite_*_*>(AnimSprite * * param_1, AnimSprite * * param_2, AnimSprite * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimSprite ** __cdecl
stdext::_Unchecked_move_backward<AnimSprite_*_*,AnimSprite_*_*>
          (AnimSprite **param_1,AnimSprite **param_2,AnimSprite **param_3)

{
  AnimSprite **ppAVar1;
  
  ppAVar1 = std::
            _Move_backward_opt<AnimSprite_*_*,AnimSprite_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppAVar1;
}
