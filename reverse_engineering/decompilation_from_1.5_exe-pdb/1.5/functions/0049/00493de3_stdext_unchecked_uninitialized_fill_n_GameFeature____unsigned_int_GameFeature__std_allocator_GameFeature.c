/*
 * Entry: 00493de3
 * Name: stdext::unchecked_uninitialized_fill_n<GameFeature_*_*,unsigned_int,GameFeature_*,std::allocator<GameFeature_*>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<GameFeature_*_*,unsigned_int,GameFeature_*,std::allocator<GameFeature_*>_>(GameFeature * * param_1, uint param_2, GameFeature * * param_3, allocator<GameFeature_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::
unchecked_uninitialized_fill_n<GameFeature_*_*,unsigned_int,GameFeature_*,std::allocator<GameFeature_*>_>
          (GameFeature **param_1,uint param_2,GameFeature **param_3,
          allocator<GameFeature_*> *param_4)

{
  unchecked_fill_n<GameFeature_*_*,unsigned_int,GameFeature_*>(param_1,param_2,param_3);
  return;
}
