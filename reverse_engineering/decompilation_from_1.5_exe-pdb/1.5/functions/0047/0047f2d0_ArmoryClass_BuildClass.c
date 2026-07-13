/*
 * Entry: 0047f2d0
 * Name: ArmoryClass::BuildClass
 * Namespace: ArmoryClass
 * Signature: GameObjectClass * BuildClass(ArmoryClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall ArmoryClass::BuildClass(ArmoryClass *this,long64 param_1)

{
  ArmoryClass *pAVar1;
  undefined4 unaff_ESI;
  
  pAVar1 = operator_new(0x4c0);
  if (pAVar1 == (ArmoryClass *)0x0) {
    pAVar1 = (ArmoryClass *)0x0;
  }
  else {
    pAVar1 = ArmoryClass(pAVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pAVar1;
}
