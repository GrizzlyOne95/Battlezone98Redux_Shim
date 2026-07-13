/*
 * Entry: 004e4d61
 * Name: std::_Uninit_fill_n<ScorePlayer_*_*,unsigned_int,ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<ScorePlayer_*_*,unsigned_int,ScorePlayer_*,std::allocator<ScorePlayer_*>_>(ScorePlayer * * param_1, uint param_2, ScorePlayer * * param_3, allocator<ScorePlayer_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<ScorePlayer_*_*,unsigned_int,ScorePlayer_*,std::allocator<ScorePlayer_*>_>
          (ScorePlayer **param_1,uint param_2,ScorePlayer **param_3,
          allocator<ScorePlayer_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<ScorePlayer_*_*,unsigned_int,ScorePlayer_*>(param_1,param_2,param_3);
  return;
}
