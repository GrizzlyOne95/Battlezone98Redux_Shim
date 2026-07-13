/*
 * Entry: 004c2dd9
 * Name: CockpitTimer::Simulate
 * Namespace: CockpitTimer
 * Signature: void Simulate(CockpitTimer * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitTimer::Simulate(CockpitTimer *this,float param_1)

{
  long *plVar1;
  float fVar2;
  
  if (this->active != false) {
    fVar2 = this->frac - param_1;
    this->frac = fVar2;
    if (fVar2 < 0.0) {
      this->frac = fVar2 + 1.0;
      if (this->countdown == false) {
        this->timer = this->timer + 1;
      }
      else {
        plVar1 = &this->timer;
        *plVar1 = *plVar1 + -1;
        if (*plVar1 == 0) {
          this->active = false;
        }
      }
    }
  }
  return;
}
