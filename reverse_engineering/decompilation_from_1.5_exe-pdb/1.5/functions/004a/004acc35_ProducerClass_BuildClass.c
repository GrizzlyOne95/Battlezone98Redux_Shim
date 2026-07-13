/*
 * Entry: 004acc35
 * Name: ProducerClass::BuildClass
 * Namespace: ProducerClass
 * Signature: GameObjectClass * BuildClass(ProducerClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall ProducerClass::BuildClass(ProducerClass *this,long64 param_1)

{
  ProducerClass *pPVar1;
  undefined4 unaff_ESI;
  
  pPVar1 = operator_new(0x430);
  if (pPVar1 == (ProducerClass *)0x0) {
    pPVar1 = (ProducerClass *)0x0;
  }
  else {
    pPVar1 = ProducerClass(pPVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pPVar1;
}
