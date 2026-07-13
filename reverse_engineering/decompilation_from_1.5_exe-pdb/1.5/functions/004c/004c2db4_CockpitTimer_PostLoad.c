/*
 * Entry: 004c2db4
 * Name: CockpitTimer::PostLoad
 * Namespace: CockpitTimer
 * Signature: void PostLoad(CockpitTimer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitTimer::PostLoad(CockpitTimer *this)

{
  if (this->show != false) {
    this->show = false;
    ShowTimer(this);
    return;
  }
  return;
}
