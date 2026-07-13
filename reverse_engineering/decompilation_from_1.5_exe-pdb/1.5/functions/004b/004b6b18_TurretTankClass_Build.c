/*
 * Entry: 004b6b18
 * Name: TurretTankClass::Build
 * Namespace: TurretTankClass
 * Signature: GameObject * Build(TurretTankClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall TurretTankClass::Build(TurretTankClass *this,_OBJ76 *param_1)

{
  TurretTank *pTVar1;
  
  pTVar1 = GameObject::operator_new(0x338);
  if (pTVar1 == (TurretTank *)0x0) {
    pTVar1 = (TurretTank *)0x0;
  }
  else {
    pTVar1 = TurretTank::TurretTank(pTVar1,param_1,this);
  }
  return (GameObject *)pTVar1;
}
