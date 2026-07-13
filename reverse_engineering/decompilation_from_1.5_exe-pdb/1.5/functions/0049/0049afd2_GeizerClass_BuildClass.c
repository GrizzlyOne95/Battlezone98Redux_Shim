/*
 * Entry: 0049afd2
 * Name: GeizerClass::BuildClass
 * Namespace: GeizerClass
 * Signature: GameObjectClass * BuildClass(GeizerClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall GeizerClass::BuildClass(GeizerClass *this,long64 param_1)

{
  GeizerClass *pGVar1;
  undefined4 unaff_ESI;
  
  pGVar1 = operator_new(0x160);
  if (pGVar1 == (GeizerClass *)0x0) {
    pGVar1 = (GeizerClass *)0x0;
  }
  else {
    pGVar1 = GeizerClass(pGVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pGVar1;
}
