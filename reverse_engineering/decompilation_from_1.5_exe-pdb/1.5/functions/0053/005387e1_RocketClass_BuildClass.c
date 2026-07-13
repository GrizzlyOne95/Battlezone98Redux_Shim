/*
 * Entry: 005387e1
 * Name: RocketClass::BuildClass
 * Namespace: RocketClass
 * Signature: OrdnanceClass * BuildClass(RocketClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall RocketClass::BuildClass(RocketClass *this,long64 param_1)

{
  RocketClass *pRVar1;
  undefined4 unaff_ESI;
  
  pRVar1 = operator_new(0xb0);
  if (pRVar1 == (RocketClass *)0x0) {
    pRVar1 = (RocketClass *)0x0;
  }
  else {
    pRVar1 = RocketClass(pRVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pRVar1;
}
