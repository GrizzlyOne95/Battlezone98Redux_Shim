/*
 * Entry: 0040ec41
 * Name: AttackTask::Load
 * Namespace: AttackTask
 * Signature: bool Load(AttackTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AttackTask::Load(AttackTask *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,&this->attackRangeSq,4);
  if ((((bVar1) && (bVar1 = ::in(param_1,&this->waitRangeSq,4), bVar1)) &&
      (bVar1 = ::in(param_1,&this->fleeFrom,4), bVar1)) &&
     (bVar1 = UnitTask::Load((UnitTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
