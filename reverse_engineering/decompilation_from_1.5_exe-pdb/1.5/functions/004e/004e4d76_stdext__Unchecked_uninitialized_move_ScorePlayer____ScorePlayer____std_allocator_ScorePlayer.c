/*
 * Entry: 004e4d76
 * Name: stdext::_Unchecked_uninitialized_move<ScorePlayer_*_*,ScorePlayer_*_*,std::allocator<ScorePlayer_*>_>
 * Namespace: stdext
 * Signature: ScorePlayer * * _Unchecked_uninitialized_move<ScorePlayer_*_*,ScorePlayer_*_*,std::allocator<ScorePlayer_*>_>(ScorePlayer * * param_1, ScorePlayer * * param_2, ScorePlayer * * param_3, allocator<ScorePlayer_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScorePlayer ** __cdecl
stdext::
_Unchecked_uninitialized_move<ScorePlayer_*_*,ScorePlayer_*_*,std::allocator<ScorePlayer_*>_>
          (ScorePlayer **param_1,ScorePlayer **param_2,ScorePlayer **param_3,
          allocator<ScorePlayer_*> *param_4)

{
  ScorePlayer **ppSVar1;
  
  ppSVar1 = std::_Uninit_copy<ScorePlayer_*_*,ScorePlayer_*_*,std::allocator<ScorePlayer_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
