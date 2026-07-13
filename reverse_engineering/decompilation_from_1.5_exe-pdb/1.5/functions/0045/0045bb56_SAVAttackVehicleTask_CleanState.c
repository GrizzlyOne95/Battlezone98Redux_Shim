/*
 * Entry: 0045bb56
 * Name: SAVAttackVehicleTask::CleanState
 * Namespace: SAVAttackVehicleTask
 * Signature: void CleanState(SAVAttackVehicleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVAttackVehicleTask::CleanState(SAVAttackVehicleTask *this)

{
  if ((*(int *)&this->field_0xc != 2) && (*(int *)&this->field_0xc != 0xf)) {
    return;
  }
  UnitTask::CleanGoto((UnitTask *)this);
  return;
}
