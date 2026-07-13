/*
 * Entry: 004d507a
 * Name: PathDisplay::InitControlPlan
 * Namespace: PathDisplay
 * Signature: void InitControlPlan(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::InitControlPlan(PathDisplay *this)

{
  this->editPathCount = 0;
  this->planTime = 0;
  this->planX0 = 1e+30;
  this->planX1 = 1e+30;
  this->planPath = (AiPath *)0x0;
  this->editPath = (AiPath *)0x0;
  return;
}
