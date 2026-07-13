/*
 * Entry: 004e4f07
 * Name: std::make_heap<ScorePlayer_*_*,king_comp>
 * Namespace: std
 * Signature: void make_heap<ScorePlayer_*_*,king_comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, king_comp param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::make_heap<ScorePlayer_*_*,king_comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,king_comp param_3)

{
  if (4 < (int)((int)param_2 - (int)param_1 & 0xfffffffcU)) {
    _Make_heap<ScorePlayer_*_*,int,ScorePlayer_*,king_comp>
              (param_1,param_2,param_3,(int *)0x0,(ScorePlayer **)0x0);
  }
  return;
}
