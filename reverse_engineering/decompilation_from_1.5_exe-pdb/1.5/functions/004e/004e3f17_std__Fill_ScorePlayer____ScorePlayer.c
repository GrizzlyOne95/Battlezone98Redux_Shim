/*
 * Entry: 004e3f17
 * Name: std::_Fill<ScorePlayer_*_*,ScorePlayer_*>
 * Namespace: std
 * Signature: void _Fill<ScorePlayer_*_*,ScorePlayer_*>(ScorePlayer * * param_1, ScorePlayer * * param_2, ScorePlayer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill<ScorePlayer_*_*,ScorePlayer_*>
          (ScorePlayer **param_1,ScorePlayer **param_2,ScorePlayer **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
