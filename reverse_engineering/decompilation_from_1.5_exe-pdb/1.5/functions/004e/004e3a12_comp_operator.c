/*
 * Entry: 004e3a12
 * Name: comp::operator()
 * Namespace: comp
 * Signature: bool operator()(comp * this, ScorePlayer * param_1, ScorePlayer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall comp::operator()(comp *this,ScorePlayer *param_1,ScorePlayer *param_2)

{
  return param_2->iKills - param_2->iDeaths < param_1->iKills - param_1->iDeaths;
}
