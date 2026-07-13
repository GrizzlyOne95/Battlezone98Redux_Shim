/*
 * Entry: 004b4a1d
 * Name: TurretCraftClass::BuildClass
 * Namespace: TurretCraftClass
 * Signature: GameObjectClass * BuildClass(TurretCraftClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall TurretCraftClass::BuildClass(TurretCraftClass *this,long64 param_1)

{
  TurretCraftClass *pTVar1;
  undefined4 unaff_ESI;
  
  pTVar1 = operator_new(0x310);
  if (pTVar1 == (TurretCraftClass *)0x0) {
    pTVar1 = (TurretCraftClass *)0x0;
  }
  else {
    pTVar1 = TurretCraftClass(pTVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pTVar1;
}
