/*
 * Entry: 00491a95
 * Name: FactoryClass::BuildClass
 * Namespace: FactoryClass
 * Signature: GameObjectClass * BuildClass(FactoryClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall FactoryClass::BuildClass(FactoryClass *this,long64 param_1)

{
  FactoryClass *pFVar1;
  undefined4 unaff_ESI;
  
  pFVar1 = operator_new(0x430);
  if (pFVar1 == (FactoryClass *)0x0) {
    pFVar1 = (FactoryClass *)0x0;
  }
  else {
    pFVar1 = FactoryClass(pFVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pFVar1;
}
