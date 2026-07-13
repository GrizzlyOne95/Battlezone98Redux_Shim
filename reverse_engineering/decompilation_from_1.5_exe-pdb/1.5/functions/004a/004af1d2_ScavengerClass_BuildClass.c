/*
 * Entry: 004af1d2
 * Name: ScavengerClass::BuildClass
 * Namespace: ScavengerClass
 * Signature: GameObjectClass * BuildClass(ScavengerClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall ScavengerClass::BuildClass(ScavengerClass *this,long64 param_1)

{
  ScavengerClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0x418);
  if (pSVar1 == (ScavengerClass *)0x0) {
    pSVar1 = (ScavengerClass *)0x0;
  }
  else {
    pSVar1 = ScavengerClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pSVar1;
}
