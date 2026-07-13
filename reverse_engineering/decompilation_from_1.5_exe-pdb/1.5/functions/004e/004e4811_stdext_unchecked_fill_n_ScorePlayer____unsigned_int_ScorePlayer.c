/*
 * Entry: 004e4811
 * Name: stdext::unchecked_fill_n<ScorePlayer_*_*,unsigned_int,ScorePlayer_*>
 * Namespace: stdext
 * Signature: void unchecked_fill_n<ScorePlayer_*_*,unsigned_int,ScorePlayer_*>(ScorePlayer * * param_1, uint param_2, ScorePlayer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_fill_n<ScorePlayer_*_*,unsigned_int,ScorePlayer_*>
          (ScorePlayer **param_1,uint param_2,ScorePlayer **param_3)

{
  std::_Fill_n<ScorePlayer_*_*,unsigned_int,ScorePlayer_*>
            (param_1,param_2,param_3,(random_access_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
