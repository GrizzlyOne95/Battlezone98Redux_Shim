/*
 * Entry: 004931d5
 * Name: stdext::_Unchecked_uninitialized_move<GameFeature_*_*,GameFeature_*_*,std::allocator<GameFeature_*>_>
 * Namespace: stdext
 * Signature: GameFeature * * _Unchecked_uninitialized_move<GameFeature_*_*,GameFeature_*_*,std::allocator<GameFeature_*>_>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, allocator<GameFeature_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameFeature ** __cdecl
stdext::
_Unchecked_uninitialized_move<GameFeature_*_*,GameFeature_*_*,std::allocator<GameFeature_*>_>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,
          allocator<GameFeature_*> *param_4)

{
  GameFeature **ppGVar1;
  
  ppGVar1 = std::_Uninit_copy<GameFeature_*_*,GameFeature_*_*,std::allocator<GameFeature_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppGVar1;
}
