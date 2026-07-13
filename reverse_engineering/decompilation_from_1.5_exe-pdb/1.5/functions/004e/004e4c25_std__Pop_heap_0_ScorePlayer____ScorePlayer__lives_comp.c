/*
 * Entry: 004e4c25
 * Name: std::_Pop_heap_0<ScorePlayer_*_*,ScorePlayer_*,lives_comp>
 * Namespace: std
 * Signature: void _Pop_heap_0<ScorePlayer_*_*,ScorePlayer_*,lives_comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, lives_comp param_3, ScorePlayer * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Pop_heap_0<ScorePlayer_*_*,ScorePlayer_*,lives_comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,lives_comp param_3,ScorePlayer **param_4)

{
  ScorePlayer **ppSVar1;
  
  ppSVar1 = param_2 + -1;
  _Pop_heap<ScorePlayer_*_*,int,ScorePlayer_*,lives_comp>
            (param_1,ppSVar1,ppSVar1,*ppSVar1,param_3,(int *)0x0);
  return;
}
