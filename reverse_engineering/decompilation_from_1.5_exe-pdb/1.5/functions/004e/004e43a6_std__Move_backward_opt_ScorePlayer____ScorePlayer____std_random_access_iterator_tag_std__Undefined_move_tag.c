/*
 * Entry: 004e43a6
 * Name: std::_Move_backward_opt<ScorePlayer_*_*,ScorePlayer_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: ScorePlayer * * _Move_backward_opt<ScorePlayer_*_*,ScorePlayer_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(ScorePlayer * * param_1, ScorePlayer * * param_2, ScorePlayer * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScorePlayer ** __cdecl
std::
_Move_backward_opt<ScorePlayer_*_*,ScorePlayer_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (ScorePlayer **param_1,ScorePlayer **param_2,ScorePlayer **param_3,
          random_access_iterator_tag param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  ScorePlayer **ppSVar1;
  
  ppSVar1 = _Copy_backward_opt<ScorePlayer_*_*,ScorePlayer_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
