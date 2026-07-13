/*
 * Entry: 00499735
 * Name: stdext::_Unchecked_move_backward<GameObjectClass_*_*,GameObjectClass_*_*>
 * Namespace: stdext
 * Signature: GameObjectClass * * _Unchecked_move_backward<GameObjectClass_*_*,GameObjectClass_*_*>(GameObjectClass * * param_1, GameObjectClass * * param_2, GameObjectClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass ** __cdecl
stdext::_Unchecked_move_backward<GameObjectClass_*_*,GameObjectClass_*_*>
          (GameObjectClass **param_1,GameObjectClass **param_2,GameObjectClass **param_3)

{
  GameObjectClass **ppGVar1;
  
  ppGVar1 = std::
            _Move_backward_opt<GameObjectClass_*_*,GameObjectClass_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppGVar1;
}
