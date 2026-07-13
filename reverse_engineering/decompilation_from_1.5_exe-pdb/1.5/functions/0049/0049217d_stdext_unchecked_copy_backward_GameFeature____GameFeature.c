/*
 * Entry: 0049217d
 * Name: stdext::unchecked_copy_backward<GameFeature_*_*,GameFeature_*_*>
 * Namespace: stdext
 * Signature: GameFeature * * unchecked_copy_backward<GameFeature_*_*,GameFeature_*_*>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameFeature ** __cdecl
stdext::unchecked_copy_backward<GameFeature_*_*,GameFeature_*_*>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3)

{
  GameFeature **ppGVar1;
  
  ppGVar1 = std::_Copy_backward_opt<GameFeature_*_*,GameFeature_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Scalar_ptr_iterator_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppGVar1;
}
