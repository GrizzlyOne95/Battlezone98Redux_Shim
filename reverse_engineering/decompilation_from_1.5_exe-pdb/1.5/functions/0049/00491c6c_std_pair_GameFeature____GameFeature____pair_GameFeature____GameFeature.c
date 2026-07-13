/*
 * Entry: 00491c6c
 * Name: std::pair<GameFeature_*_*,GameFeature_*_*>::pair<GameFeature_*_*,GameFeature_*_*>
 * Namespace: std::pair<GameFeature_*_*,GameFeature_*_*>
 * Signature: pair<GameFeature_*_*,GameFeature_*_*> * pair<GameFeature_*_*,GameFeature_*_*>(pair<GameFeature_*_*,GameFeature_*_*> * this, GameFeature * * * param_1, GameFeature * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<GameFeature_*_*,GameFeature_*_*> * __thiscall
std::pair<GameFeature_*_*,GameFeature_*_*>::pair<GameFeature_*_*,GameFeature_*_*>
          (pair<GameFeature_*_*,GameFeature_*_*> *this,GameFeature ***param_1,GameFeature ***param_2
          )

{
  this->first = *param_1;
  this->second = *param_2;
  return this;
}
