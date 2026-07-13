/*
 * Entry: 004676e7
 * Name: TurretAttack::CleanState
 * Namespace: TurretAttack
 * Signature: void CleanState(TurretAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretAttack::CleanState(TurretAttack *this)

{
  int iVar1;
  
  iVar1 = this->_padding_;
  if (iVar1 != 2) {
    if (iVar1 == 3) {
      UnitTask::CleanStuck((UnitTask *)this);
      return;
    }
    if (iVar1 == 5) {
      UnitTask::CleanSpecial((UnitTask *)this);
      return;
    }
    if ((iVar1 < 0xb) || (0xc < iVar1)) {
      return;
    }
  }
  UnitTask::CleanGoto((UnitTask *)this);
  return;
}
