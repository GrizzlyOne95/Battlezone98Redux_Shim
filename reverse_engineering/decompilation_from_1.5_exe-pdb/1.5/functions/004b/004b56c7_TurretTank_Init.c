/*
 * Entry: 004b56c7
 * Name: TurretTank::Init
 * Namespace: TurretTank
 * Signature: void Init(TurretTank * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTank::Init(TurretTank *this,int param_1)

{
  Craft::Init((Craft *)this,param_1);
  if (this->_padding_ == 2) {
    SetHazard(this);
  }
  return;
}
