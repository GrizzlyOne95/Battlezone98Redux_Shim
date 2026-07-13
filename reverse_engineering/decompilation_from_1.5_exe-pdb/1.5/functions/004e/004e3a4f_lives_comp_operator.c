/*
 * Entry: 004e3a4f
 * Name: lives_comp::operator()
 * Namespace: lives_comp
 * Signature: bool operator()(lives_comp * this, ScorePlayer * param_1, ScorePlayer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall lives_comp::operator()(lives_comp *this,ScorePlayer *param_1,ScorePlayer *param_2)

{
  return param_2->iLives < param_1->iLives;
}
