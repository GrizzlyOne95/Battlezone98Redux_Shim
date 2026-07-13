/*
 * Entry: 004927df
 * Name: std::_Uninit_move<GameFeature_*_*,GameFeature_*_*,std::allocator<GameFeature_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: GameFeature * * _Uninit_move<GameFeature_*_*,GameFeature_*_*,std::allocator<GameFeature_*>,std::_Undefined_move_tag>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, allocator<GameFeature_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameFeature ** __cdecl
std::
_Uninit_move<GameFeature_*_*,GameFeature_*_*,std::allocator<GameFeature_*>,std::_Undefined_move_tag>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,
          allocator<GameFeature_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  GameFeature **ppGVar1;
  
  ppGVar1 = stdext::
            unchecked_uninitialized_copy<GameFeature_*_*,GameFeature_*_*,std::allocator<GameFeature_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppGVar1;
}
