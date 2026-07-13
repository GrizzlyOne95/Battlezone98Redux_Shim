/*
 * Entry: 004e3f96
 * Name: std::swap<ScorePlayer_*>
 * Namespace: std
 * Signature: void swap<ScorePlayer_*>(ScorePlayer * * param_1, ScorePlayer * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::swap<ScorePlayer_*>(ScorePlayer **param_1,ScorePlayer **param_2)

{
  ScorePlayer *pSVar1;
  
  if (param_1 != param_2) {
    pSVar1 = *param_1;
    *param_1 = *param_2;
    *param_2 = pSVar1;
  }
  return;
}
