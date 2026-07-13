/*
 * Entry: 004b094b
 * Name: ScrapSiloClass::BuildClass
 * Namespace: ScrapSiloClass
 * Signature: GameObjectClass * BuildClass(ScrapSiloClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall ScrapSiloClass::BuildClass(ScrapSiloClass *this,long64 param_1)

{
  ScrapSiloClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0x168);
  if (pSVar1 == (ScrapSiloClass *)0x0) {
    pSVar1 = (ScrapSiloClass *)0x0;
  }
  else {
    pSVar1 = ScrapSiloClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pSVar1;
}
