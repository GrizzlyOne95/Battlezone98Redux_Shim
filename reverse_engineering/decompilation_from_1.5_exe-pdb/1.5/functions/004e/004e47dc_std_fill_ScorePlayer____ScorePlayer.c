/*
 * Entry: 004e47dc
 * Name: std::fill<ScorePlayer_*_*,ScorePlayer_*>
 * Namespace: std
 * Signature: void fill<ScorePlayer_*_*,ScorePlayer_*>(ScorePlayer * * param_1, ScorePlayer * * param_2, ScorePlayer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<ScorePlayer_*_*,ScorePlayer_*>
          (ScorePlayer **param_1,ScorePlayer **param_2,ScorePlayer **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
