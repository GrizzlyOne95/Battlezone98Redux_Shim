/*
 * Entry: 00467642
 * Name: TurretAttack::Load
 * Namespace: TurretAttack
 * Signature: bool Load(TurretAttack * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretAttack::Load(TurretAttack *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,&this->attackRangeSq,4);
  if (((bVar1) && (bVar1 = ::in(param_1,&this->waitRangeSq,4), bVar1)) &&
     (bVar1 = UnitTask::Load((UnitTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
