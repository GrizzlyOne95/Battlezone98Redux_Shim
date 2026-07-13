/*
 * Entry: 004e3a30
 * Name: king_comp::operator()
 * Namespace: king_comp
 * Signature: bool operator()(king_comp * this, ScorePlayer * param_1, ScorePlayer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall king_comp::operator()(king_comp *this,ScorePlayer *param_1,ScorePlayer *param_2)

{
  return param_2->fTimeInZone < param_1->fTimeInZone;
}
