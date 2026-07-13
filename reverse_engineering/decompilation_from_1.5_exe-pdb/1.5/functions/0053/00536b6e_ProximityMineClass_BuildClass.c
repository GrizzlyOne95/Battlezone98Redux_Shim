/*
 * Entry: 00536b6e
 * Name: ProximityMineClass::BuildClass
 * Namespace: ProximityMineClass
 * Signature: GameObjectClass * BuildClass(ProximityMineClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall ProximityMineClass::BuildClass(ProximityMineClass *this,long64 param_1)

{
  ProximityMineClass *pPVar1;
  undefined4 unaff_ESI;
  
  pPVar1 = operator_new(0x178);
  if (pPVar1 == (ProximityMineClass *)0x0) {
    pPVar1 = (ProximityMineClass *)0x0;
  }
  else {
    pPVar1 = ProximityMineClass(pPVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pPVar1;
}
