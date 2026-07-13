/*
 * Entry: 0049f5fc
 * Name: TurretTank::IsSnipable
 * Namespace: TurretTank
 * Signature: bool IsSnipable(TurretTank * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretTank::IsSnipable(TurretTank *this)

{
  bool bVar1;
  
  bVar1 = false;
  if ((this->_padding_ != 2) && (this->_padding_ != 0)) {
    bVar1 = true;
  }
  return bVar1;
}
