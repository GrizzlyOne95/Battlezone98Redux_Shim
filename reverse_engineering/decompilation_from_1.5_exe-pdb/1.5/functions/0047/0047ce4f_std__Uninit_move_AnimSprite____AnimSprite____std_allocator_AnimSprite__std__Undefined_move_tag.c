/*
 * Entry: 0047ce4f
 * Name: std::_Uninit_move<AnimSprite_*_*,AnimSprite_*_*,std::allocator<AnimSprite_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: AnimSprite * * _Uninit_move<AnimSprite_*_*,AnimSprite_*_*,std::allocator<AnimSprite_*>,std::_Undefined_move_tag>(AnimSprite * * param_1, AnimSprite * * param_2, AnimSprite * * param_3, allocator<AnimSprite_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimSprite ** __cdecl
std::
_Uninit_move<AnimSprite_*_*,AnimSprite_*_*,std::allocator<AnimSprite_*>,std::_Undefined_move_tag>
          (AnimSprite **param_1,AnimSprite **param_2,AnimSprite **param_3,
          allocator<AnimSprite_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  AnimSprite **ppAVar1;
  
  ppAVar1 = stdext::
            unchecked_uninitialized_copy<AnimSprite_*_*,AnimSprite_*_*,std::allocator<AnimSprite_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppAVar1;
}
