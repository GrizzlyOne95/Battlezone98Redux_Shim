/*
 * Entry: 004994be
 * Name: std::_Uninit_copy<GameObjectClass_*_*,GameObjectClass_*_*,std::allocator<GameObjectClass_*>_>
 * Namespace: std
 * Signature: GameObjectClass * * _Uninit_copy<GameObjectClass_*_*,GameObjectClass_*_*,std::allocator<GameObjectClass_*>_>(GameObjectClass * * param_1, GameObjectClass * * param_2, GameObjectClass * * param_3, allocator<GameObjectClass_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass ** __cdecl
std::_Uninit_copy<GameObjectClass_*_*,GameObjectClass_*_*,std::allocator<GameObjectClass_*>_>
          (GameObjectClass **param_1,GameObjectClass **param_2,GameObjectClass **param_3,
          allocator<GameObjectClass_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
