/*
 * Entry: 0046ad34
 * Name: UnitTask::DoCircle
 * Namespace: UnitTask
 * Signature: void DoCircle(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::DoCircle(UnitTask *this)

{
  VEHICLE *pVVar1;
  
  pVVar1 = this->me->vhcl;
  (pVVar1->control).turbo = 0;
  (pVVar1->control).steer = 0.25;
  (pVVar1->control).braccel = 0.25;
  (pVVar1->control).strafe = 0.0;
  return;
}
