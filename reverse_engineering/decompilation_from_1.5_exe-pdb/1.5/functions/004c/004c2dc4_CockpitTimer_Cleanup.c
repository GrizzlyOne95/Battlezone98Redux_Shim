/*
 * Entry: 004c2dc4
 * Name: CockpitTimer::Cleanup
 * Namespace: CockpitTimer
 * Signature: void Cleanup(CockpitTimer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitTimer::Cleanup(CockpitTimer *this)

{
  if (this->active != false) {
    this->active = false;
  }
  if (this->show != false) {
    HideTimer(this);
    return;
  }
  return;
}
