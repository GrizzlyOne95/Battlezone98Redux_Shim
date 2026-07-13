/*
 * Entry: 00416727
 * Name: CockpitTimer::SetTimerUp
 * Namespace: CockpitTimer
 * Signature: void SetTimerUp(CockpitTimer * this, long param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitTimer::SetTimerUp(CockpitTimer *this,long param_1,long param_2,long param_3)

{
  this->timer = param_1;
  this->frac = 1.0;
  this->warn = param_2;
  this->alert = param_3;
  this->countdown = false;
  this->active = true;
  this->hours = true;
  return;
}
