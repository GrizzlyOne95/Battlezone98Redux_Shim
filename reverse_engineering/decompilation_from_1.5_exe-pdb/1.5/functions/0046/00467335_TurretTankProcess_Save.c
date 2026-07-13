/*
 * Entry: 00467335
 * Name: TurretTankProcess::Save
 * Namespace: TurretTankProcess
 * Signature: bool Save(TurretTankProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretTankProcess::Save(TurretTankProcess *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->waitDeploy,1,"waitDeploy");
  if ((((bVar1) && (bVar1 = ::out(param_1,&this->waitDeployTime,4,"waitDeployTime"), bVar1)) &&
      (bVar1 = ::out(param_1,&this->nextAttackTime,4,"nextAttackTime"), bVar1)) &&
     ((bVar1 = ::out(param_1,&this->attackUser,1,"attackUser"), bVar1 &&
      (bVar1 = UnitProcess::Save((UnitProcess *)this,param_1), bVar1)))) {
    return true;
  }
  return false;
}
