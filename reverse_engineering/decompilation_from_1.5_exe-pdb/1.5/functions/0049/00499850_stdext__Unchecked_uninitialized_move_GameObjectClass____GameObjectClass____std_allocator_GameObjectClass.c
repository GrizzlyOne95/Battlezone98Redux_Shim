/*
 * Entry: 00499850
 * Name: stdext::_Unchecked_uninitialized_move<GameObjectClass_*_*,GameObjectClass_*_*,std::allocator<GameObjectClass_*>_>
 * Namespace: stdext
 * Signature: GameObjectClass * * _Unchecked_uninitialized_move<GameObjectClass_*_*,GameObjectClass_*_*,std::allocator<GameObjectClass_*>_>(GameObjectClass * * param_1, GameObjectClass * * param_2, GameObjectClass * * param_3, allocator<GameObjectClass_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass ** __cdecl
stdext::
_Unchecked_uninitialized_move<GameObjectClass_*_*,GameObjectClass_*_*,std::allocator<GameObjectClass_*>_>
          (GameObjectClass **param_1,GameObjectClass **param_2,GameObjectClass **param_3,
          allocator<GameObjectClass_*> *param_4)

{
  GameObjectClass **ppGVar1;
  
  ppGVar1 = std::
            _Uninit_copy<GameObjectClass_*_*,GameObjectClass_*_*,std::allocator<GameObjectClass_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppGVar1;
}
