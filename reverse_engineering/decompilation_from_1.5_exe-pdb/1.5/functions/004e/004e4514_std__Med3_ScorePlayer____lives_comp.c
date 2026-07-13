/*
 * Entry: 004e4514
 * Name: std::_Med3<ScorePlayer_*_*,lives_comp>
 * Namespace: std
 * Signature: void _Med3<ScorePlayer_*_*,lives_comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, ScorePlayer * * param_3, lives_comp param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Med3<ScorePlayer_*_*,lives_comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,ScorePlayer **param_3,lives_comp param_4)

{
  if ((*param_1)->iLives < (*param_2)->iLives) {
    swap<ScorePlayer_*>(param_2,param_1);
  }
  if ((*param_2)->iLives < (*param_3)->iLives) {
    swap<ScorePlayer_*>(param_3,param_2);
  }
  if ((*param_1)->iLives < (*param_2)->iLives) {
    swap<ScorePlayer_*>(param_2,param_1);
  }
  return;
}
