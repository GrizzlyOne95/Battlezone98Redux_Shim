/*
 * Entry: 0047c9e4
 * Name: std::_Move_backward_opt<AnimSprite_*_*,AnimSprite_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: AnimSprite * * _Move_backward_opt<AnimSprite_*_*,AnimSprite_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(AnimSprite * * param_1, AnimSprite * * param_2, AnimSprite * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimSprite ** __cdecl
std::
_Move_backward_opt<AnimSprite_*_*,AnimSprite_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (AnimSprite **param_1,AnimSprite **param_2,AnimSprite **param_3,
          random_access_iterator_tag param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  AnimSprite **ppAVar1;
  
  ppAVar1 = _Copy_backward_opt<AnimSprite_*_*,AnimSprite_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppAVar1;
}
