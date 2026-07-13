/*
 * Entry: 00467574
 * Name: TurretBlastAttack::InitState
 * Namespace: TurretBlastAttack
 * Signature: void InitState(TurretBlastAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretBlastAttack::InitState(TurretBlastAttack *this)

{
  if (*(int *)&this->field_0xc == 5) {
    UnitTask::InitSpecial((UnitTask *)this);
    *(undefined4 *)&this->field_0xb4 =
         *(undefined4 *)(*(int *)(*(int *)&this->field_0x14 + 0x228) + 200);
  }
  return;
}
