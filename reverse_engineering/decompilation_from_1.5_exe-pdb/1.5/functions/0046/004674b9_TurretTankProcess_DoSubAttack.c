/*
 * Entry: 004674b9
 * Name: TurretTankProcess::DoSubAttack
 * Namespace: TurretTankProcess
 * Signature: void DoSubAttack(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::DoSubAttack(TurretTankProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(*(int *)this->_padding_ + 0x18))();
  if (cVar1 == '\0') {
                    /* WARNING: Could not recover jumptable at 0x004674ce. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(int *)this->_padding_ + 0x1c))();
    return;
  }
  return;
}
