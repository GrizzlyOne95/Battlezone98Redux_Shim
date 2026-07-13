/*
 * Entry: 004e43d6
 * Name: std::iter_swap<ScorePlayer_*_*,ScorePlayer_*_*>
 * Namespace: std
 * Signature: void iter_swap<ScorePlayer_*_*,ScorePlayer_*_*>(ScorePlayer * * param_1, ScorePlayer * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::iter_swap<ScorePlayer_*_*,ScorePlayer_*_*>(ScorePlayer **param_1,ScorePlayer **param_2)

{
  ScorePlayer *pSVar1;
  
  if (param_1 != param_2) {
    pSVar1 = *param_1;
    *param_1 = *param_2;
    *param_2 = pSVar1;
  }
  return;
}
