/*
 * Entry: 004e47e1
 * Name: stdext::_Unchecked_move_backward<ScorePlayer_*_*,ScorePlayer_*_*>
 * Namespace: stdext
 * Signature: ScorePlayer * * _Unchecked_move_backward<ScorePlayer_*_*,ScorePlayer_*_*>(ScorePlayer * * param_1, ScorePlayer * * param_2, ScorePlayer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScorePlayer ** __cdecl
stdext::_Unchecked_move_backward<ScorePlayer_*_*,ScorePlayer_*_*>
          (ScorePlayer **param_1,ScorePlayer **param_2,ScorePlayer **param_3)

{
  ScorePlayer **ppSVar1;
  
  ppSVar1 = std::
            _Move_backward_opt<ScorePlayer_*_*,ScorePlayer_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
