/*
 * Entry: 00467599
 * Name: TurretBlastAttack::CleanState
 * Namespace: TurretBlastAttack
 * Signature: void CleanState(TurretBlastAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretBlastAttack::CleanState(TurretBlastAttack *this)

{
  if (*(int *)&this->field_0xc == 5) {
    UnitTask::CleanSpecial((UnitTask *)this);
    return;
  }
  return;
}
