/*
 * Entry: 0053a70d
 * Name: SprayBuildingClass::BuildClass
 * Namespace: SprayBuildingClass
 * Signature: GameObjectClass * BuildClass(SprayBuildingClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall SprayBuildingClass::BuildClass(SprayBuildingClass *this,long64 param_1)

{
  SprayBuildingClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0x188);
  if (pSVar1 == (SprayBuildingClass *)0x0) {
    pSVar1 = (SprayBuildingClass *)0x0;
  }
  else {
    pSVar1 = SprayBuildingClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pSVar1;
}
