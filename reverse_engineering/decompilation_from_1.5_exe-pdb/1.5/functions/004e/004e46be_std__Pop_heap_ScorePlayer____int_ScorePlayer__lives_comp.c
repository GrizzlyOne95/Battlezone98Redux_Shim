/*
 * Entry: 004e46be
 * Name: std::_Pop_heap<ScorePlayer_*_*,int,ScorePlayer_*,lives_comp>
 * Namespace: std
 * Signature: void _Pop_heap<ScorePlayer_*_*,int,ScorePlayer_*,lives_comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, ScorePlayer * * param_3, ScorePlayer * param_4, lives_comp param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Pop_heap<ScorePlayer_*_*,int,ScorePlayer_*,lives_comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,ScorePlayer **param_3,ScorePlayer *param_4,
          lives_comp param_5,int *param_6)

{
  *param_3 = *param_1;
  _Adjust_heap<ScorePlayer_*_*,int,ScorePlayer_*,lives_comp>
            (param_1,0,(int)param_2 - (int)param_1 >> 2,param_4,param_5);
  return;
}
