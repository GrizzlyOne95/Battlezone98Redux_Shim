/*
 * Entry: 004afdd2
 * Name: ScrapFieldClass::BuildClass
 * Namespace: ScrapFieldClass
 * Signature: GameObjectClass * BuildClass(ScrapFieldClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall ScrapFieldClass::BuildClass(ScrapFieldClass *this,long64 param_1)

{
  ScrapFieldClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0x160);
  if (pSVar1 == (ScrapFieldClass *)0x0) {
    pSVar1 = (ScrapFieldClass *)0x0;
  }
  else {
    pSVar1 = ScrapFieldClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pSVar1;
}
