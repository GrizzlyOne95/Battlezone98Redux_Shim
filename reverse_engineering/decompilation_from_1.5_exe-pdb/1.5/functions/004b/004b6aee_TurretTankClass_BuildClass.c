/*
 * Entry: 004b6aee
 * Name: TurretTankClass::BuildClass
 * Namespace: TurretTankClass
 * Signature: GameObjectClass * BuildClass(TurretTankClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall TurretTankClass::BuildClass(TurretTankClass *this,long64 param_1)

{
  TurretTankClass *pTVar1;
  undefined4 unaff_ESI;
  
  pTVar1 = operator_new(0x3d0);
  if (pTVar1 == (TurretTankClass *)0x0) {
    pTVar1 = (TurretTankClass *)0x0;
  }
  else {
    pTVar1 = TurretTankClass(pTVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pTVar1;
}
