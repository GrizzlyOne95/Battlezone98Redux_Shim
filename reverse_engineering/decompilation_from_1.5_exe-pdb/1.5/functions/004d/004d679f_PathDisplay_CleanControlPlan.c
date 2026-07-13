/*
 * Entry: 004d679f
 * Name: PathDisplay::CleanControlPlan
 * Namespace: PathDisplay
 * Signature: void CleanControlPlan(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::CleanControlPlan(PathDisplay *this)

{
  AiPath *this_00;
  
  this_00 = (AiPath *)this->editPathCount;
  if (this_00 != (AiPath *)0x0) {
    AiPath::~AiPath(this_00);
    operator_delete(this_00);
    this->editPathCount = 0;
  }
  return;
}
