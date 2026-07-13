/*
 * Entry: 005307ef
 * Name: Launcher::UpdateTimer
 * Namespace: Launcher
 * Signature: void UpdateTimer(Launcher * this, GameObject * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Launcher::UpdateTimer(Launcher *this,GameObject *param_1,float param_2)

{
  this->lockTimer = param_2 + this->lockTimer;
  return;
}
