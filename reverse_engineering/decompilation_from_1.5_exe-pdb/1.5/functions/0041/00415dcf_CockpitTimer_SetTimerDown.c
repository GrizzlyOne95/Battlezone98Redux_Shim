/*
 * Entry: 00415dcf
 * Name: CockpitTimer::SetTimerDown
 * Namespace: CockpitTimer
 * Signature: void SetTimerDown(CockpitTimer * this, long param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
CockpitTimer::SetTimerDown(CockpitTimer *this,long param_1,long param_2,long param_3)

{
  this->frac = 1.0;
  this->timer = param_1;
  this->warn = param_2;
  this->alert = param_3;
  this->countdown = true;
  this->active = true;
  this->hours = 0xe0f < param_1;
  return;
}
