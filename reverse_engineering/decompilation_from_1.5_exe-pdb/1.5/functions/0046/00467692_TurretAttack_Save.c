/*
 * Entry: 00467692
 * Name: TurretAttack::Save
 * Namespace: TurretAttack
 * Signature: bool Save(TurretAttack * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretAttack::Save(TurretAttack *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->attackRangeSq,4,"attackRangeSq");
  if (((bVar1) && (bVar1 = ::out(param_1,&this->waitRangeSq,4,"waitRangeSq"), bVar1)) &&
     (bVar1 = UnitTask::Save((UnitTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
