/*
 * Entry: 0046ba3c
 * Name: UnitTask::CleanGoto
 * Namespace: UnitTask
 * Signature: void CleanGoto(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::CleanGoto(UnitTask *this)

{
  AiPath *this_00;
  
  this_00 = this->plan;
  if (this_00 != (AiPath *)0x0) {
    AiPath::~AiPath(this_00);
    operator_delete(this_00);
    this->plan = (AiPath *)0x0;
  }
  return;
}
