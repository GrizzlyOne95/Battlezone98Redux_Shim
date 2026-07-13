/*
 * Entry: 0047be9a
 * Name: AmmoPowerupClass::BuildClass
 * Namespace: AmmoPowerupClass
 * Signature: GameObjectClass * BuildClass(AmmoPowerupClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall AmmoPowerupClass::BuildClass(AmmoPowerupClass *this,long64 param_1)

{
  AmmoPowerupClass *pAVar1;
  undefined4 unaff_ESI;
  
  pAVar1 = operator_new(0x178);
  if (pAVar1 == (AmmoPowerupClass *)0x0) {
    pAVar1 = (AmmoPowerupClass *)0x0;
  }
  else {
    pAVar1 = AmmoPowerupClass(pAVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pAVar1;
}
