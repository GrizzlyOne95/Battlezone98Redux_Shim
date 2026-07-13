/*
 * Entry: 004af761
 * Name: ScrapClass::BuildClass
 * Namespace: ScrapClass
 * Signature: GameObjectClass * BuildClass(ScrapClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall ScrapClass::BuildClass(ScrapClass *this,long64 param_1)

{
  ScrapClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0x160);
  if (pSVar1 == (ScrapClass *)0x0) {
    pSVar1 = (ScrapClass *)0x0;
  }
  else {
    pSVar1 = ScrapClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pSVar1;
}
