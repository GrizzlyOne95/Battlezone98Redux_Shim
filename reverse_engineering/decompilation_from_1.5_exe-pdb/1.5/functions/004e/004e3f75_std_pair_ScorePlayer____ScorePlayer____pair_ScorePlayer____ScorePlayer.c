/*
 * Entry: 004e3f75
 * Name: std::pair<ScorePlayer_*_*,ScorePlayer_*_*>::pair<ScorePlayer_*_*,ScorePlayer_*_*>
 * Namespace: std::pair<ScorePlayer_*_*,ScorePlayer_*_*>
 * Signature: pair<ScorePlayer_*_*,ScorePlayer_*_*> * pair<ScorePlayer_*_*,ScorePlayer_*_*>(pair<ScorePlayer_*_*,ScorePlayer_*_*> * this, ScorePlayer * * * param_1, ScorePlayer * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<ScorePlayer_*_*,ScorePlayer_*_*> * __thiscall
std::pair<ScorePlayer_*_*,ScorePlayer_*_*>::pair<ScorePlayer_*_*,ScorePlayer_*_*>
          (pair<ScorePlayer_*_*,ScorePlayer_*_*> *this,ScorePlayer ***param_1,ScorePlayer ***param_2
          )

{
  this->first = *param_1;
  this->second = *param_2;
  return this;
}
