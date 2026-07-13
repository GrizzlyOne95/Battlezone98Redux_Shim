/*
 * Entry: 004e4836
 * Name: std::_Uninit_move<ScorePlayer_*_*,ScorePlayer_*_*,std::allocator<ScorePlayer_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: ScorePlayer * * _Uninit_move<ScorePlayer_*_*,ScorePlayer_*_*,std::allocator<ScorePlayer_*>,std::_Undefined_move_tag>(ScorePlayer * * param_1, ScorePlayer * * param_2, ScorePlayer * * param_3, allocator<ScorePlayer_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScorePlayer ** __cdecl
std::
_Uninit_move<ScorePlayer_*_*,ScorePlayer_*_*,std::allocator<ScorePlayer_*>,std::_Undefined_move_tag>
          (ScorePlayer **param_1,ScorePlayer **param_2,ScorePlayer **param_3,
          allocator<ScorePlayer_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  ScorePlayer **ppSVar1;
  
  ppSVar1 = stdext::
            unchecked_uninitialized_copy<ScorePlayer_*_*,ScorePlayer_*_*,std::allocator<ScorePlayer_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppSVar1;
}
