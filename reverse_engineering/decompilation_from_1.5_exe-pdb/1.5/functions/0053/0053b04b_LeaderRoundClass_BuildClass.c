/*
 * Entry: 0053b04b
 * Name: LeaderRoundClass::BuildClass
 * Namespace: LeaderRoundClass
 * Signature: OrdnanceClass * BuildClass(LeaderRoundClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall LeaderRoundClass::BuildClass(LeaderRoundClass *this,long64 param_1)

{
  LeaderRoundClass *pLVar1;
  undefined4 unaff_ESI;
  
  pLVar1 = operator_new(0xb8);
  if (pLVar1 == (LeaderRoundClass *)0x0) {
    pLVar1 = (LeaderRoundClass *)0x0;
  }
  else {
    pLVar1 = LeaderRoundClass(pLVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pLVar1;
}
