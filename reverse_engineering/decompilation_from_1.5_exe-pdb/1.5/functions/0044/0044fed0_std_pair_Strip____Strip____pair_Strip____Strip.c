/*
 * Entry: 0044fed0
 * Name: std::pair<Strip_*_*,Strip_*_*>::pair<Strip_*_*,Strip_*_*>
 * Namespace: std::pair<Strip_*_*,Strip_*_*>
 * Signature: pair<Strip_*_*,Strip_*_*> * pair<Strip_*_*,Strip_*_*>(pair<Strip_*_*,Strip_*_*> * this, Strip * * * param_1, Strip * * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<Strip_*_*,Strip_*_*> * __thiscall
std::pair<Strip_*_*,Strip_*_*>::pair<Strip_*_*,Strip_*_*>
          (pair<Strip_*_*,Strip_*_*> *this,Strip ***param_1,Strip ***param_2)

{
  this->first = *param_1;
  this->second = *param_2;
  return this;
}
