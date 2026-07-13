/*
 * Entry: 00459ff2
 * Name: ScavGotoRepair::DoNear
 * Namespace: ScavGotoRepair
 * Signature: bool DoNear(ScavGotoRepair * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScavGotoRepair::DoNear(ScavGotoRepair *this)

{
  float10 fVar1;
  
  fVar1 = (float10)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0x1c))();
  if (fVar1 < (float10)0.95) {
    UnitTask::DoSit((UnitTask *)this);
  }
  else {
    *(undefined4 *)&this->field_0x10 = 0xd;
  }
  return false;
}
