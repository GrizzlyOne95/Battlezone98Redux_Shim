/*
 * Entry: 004e530f
 * Name: std::pop_heap<ScorePlayer_*_*,comp>
 * Namespace: std
 * Signature: void pop_heap<ScorePlayer_*_*,comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, comp param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::pop_heap<ScorePlayer_*_*,comp>(ScorePlayer **param_1,ScorePlayer **param_2,comp param_3)

{
  if (4 < (int)((int)param_2 - (int)param_1 & 0xfffffffcU)) {
    _Pop_heap_0<ScorePlayer_*_*,ScorePlayer_*,comp>(param_1,param_2,param_3,(ScorePlayer **)0x0);
  }
  return;
}
