/*
 * Entry: 0046ad5a
 * Name: UnitTask::DoCoast
 * Namespace: UnitTask
 * Signature: void DoCoast(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::DoCoast(UnitTask *this)

{
  VEHICLE *pVVar1;
  
  pVVar1 = this->me->vhcl;
  (pVVar1->control).turbo = 0;
  (pVVar1->control).steer = 0.0;
  (pVVar1->control).braccel = 0.0;
  (pVVar1->control).strafe = 0.0;
  return;
}
