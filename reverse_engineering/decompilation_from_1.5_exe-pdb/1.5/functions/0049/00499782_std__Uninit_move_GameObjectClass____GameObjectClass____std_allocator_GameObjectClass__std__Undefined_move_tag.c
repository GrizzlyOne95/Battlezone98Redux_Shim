/*
 * Entry: 00499782
 * Name: std::_Uninit_move<GameObjectClass_*_*,GameObjectClass_*_*,std::allocator<GameObjectClass_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: GameObjectClass * * _Uninit_move<GameObjectClass_*_*,GameObjectClass_*_*,std::allocator<GameObjectClass_*>,std::_Undefined_move_tag>(GameObjectClass * * param_1, GameObjectClass * * param_2, GameObjectClass * * param_3, allocator<GameObjectClass_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass ** __cdecl
std::
_Uninit_move<GameObjectClass_*_*,GameObjectClass_*_*,std::allocator<GameObjectClass_*>,std::_Undefined_move_tag>
          (GameObjectClass **param_1,GameObjectClass **param_2,GameObjectClass **param_3,
          allocator<GameObjectClass_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  GameObjectClass **ppGVar1;
  
  ppGVar1 = stdext::
            unchecked_uninitialized_copy<GameObjectClass_*_*,GameObjectClass_*_*,std::allocator<GameObjectClass_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppGVar1;
}
