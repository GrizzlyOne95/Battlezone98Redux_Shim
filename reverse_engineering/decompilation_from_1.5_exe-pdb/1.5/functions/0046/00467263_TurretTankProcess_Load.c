/*
 * Entry: 00467263
 * Name: TurretTankProcess::Load
 * Namespace: TurretTankProcess
 * Signature: bool Load(TurretTankProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretTankProcess::Load(TurretTankProcess *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,&this->waitDeploy,1);
  if ((((bVar1) && (bVar1 = ::in(param_1,&this->waitDeployTime,4), bVar1)) &&
      (bVar1 = ::in(param_1,&this->nextAttackTime,4), bVar1)) &&
     ((bVar1 = ::in(param_1,&this->attackUser,1), bVar1 &&
      (bVar1 = UnitProcess::Load((UnitProcess *)this,param_1), bVar1)))) {
    return true;
  }
  return false;
}
