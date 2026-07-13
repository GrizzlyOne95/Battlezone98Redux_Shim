/*
 * Entry: 00530925
 * Name: Launcher::Deselect
 * Namespace: Launcher
 * Signature: void Deselect(Launcher * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Launcher::Deselect(Launcher *this)

{
  this->lockTimer = 0.0;
  this->selected = false;
  this->curTarget = 0;
  this->lockTarget = 0;
  this->lockState = 0;
  return;
}
