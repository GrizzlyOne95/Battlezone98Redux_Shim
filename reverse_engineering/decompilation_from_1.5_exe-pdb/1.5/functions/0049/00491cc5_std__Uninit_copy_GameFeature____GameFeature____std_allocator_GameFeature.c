/*
 * Entry: 00491cc5
 * Name: std::_Uninit_copy<GameFeature_*_*,GameFeature_*_*,std::allocator<GameFeature_*>_>
 * Namespace: std
 * Signature: GameFeature * * _Uninit_copy<GameFeature_*_*,GameFeature_*_*,std::allocator<GameFeature_*>_>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, allocator<GameFeature_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameFeature ** __cdecl
std::_Uninit_copy<GameFeature_*_*,GameFeature_*_*,std::allocator<GameFeature_*>_>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,
          allocator<GameFeature_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
