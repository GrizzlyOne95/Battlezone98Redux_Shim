/*
 * Entry: 004cf06b
 * Name: InfoDisplay::ToggleObjectives
 * Namespace: InfoDisplay
 * Signature: void ToggleObjectives(InfoDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall InfoDisplay::ToggleObjectives(InfoDisplay *this)

{
  float fVar1;
  
  fVar1 = Get_TimeLocal();
  if (this->objectiveLast <= fVar1) {
    fVar1 = 1e+30;
  }
  else {
    fVar1 = 0.0;
  }
  this->objectiveLast = fVar1;
  return;
}
