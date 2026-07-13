/*
 * Entry: 004931c0
 * Name: std::_Uninit_fill_n<GameFeature_*_*,unsigned_int,GameFeature_*,std::allocator<GameFeature_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<GameFeature_*_*,unsigned_int,GameFeature_*,std::allocator<GameFeature_*>_>(GameFeature * * param_1, uint param_2, GameFeature * * param_3, allocator<GameFeature_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<GameFeature_*_*,unsigned_int,GameFeature_*,std::allocator<GameFeature_*>_>
          (GameFeature **param_1,uint param_2,GameFeature **param_3,
          allocator<GameFeature_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<GameFeature_*_*,unsigned_int,GameFeature_*>(param_1,param_2,param_3);
  return;
}
