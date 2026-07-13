/*
 * Entry: 0049278a
 * Name: stdext::_Unchecked_move_backward<GameFeature_*_*,GameFeature_*_*>
 * Namespace: stdext
 * Signature: GameFeature * * _Unchecked_move_backward<GameFeature_*_*,GameFeature_*_*>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameFeature ** __cdecl
stdext::_Unchecked_move_backward<GameFeature_*_*,GameFeature_*_*>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3)

{
  GameFeature **ppGVar1;
  
  ppGVar1 = std::
            _Move_backward_opt<GameFeature_*_*,GameFeature_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppGVar1;
}
