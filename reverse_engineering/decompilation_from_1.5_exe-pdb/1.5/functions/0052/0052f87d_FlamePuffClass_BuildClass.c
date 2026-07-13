/*
 * Entry: 0052f87d
 * Name: FlamePuffClass::BuildClass
 * Namespace: FlamePuffClass
 * Signature: OrdnanceClass * BuildClass(FlamePuffClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall FlamePuffClass::BuildClass(FlamePuffClass *this,long64 param_1)

{
  FlamePuffClass *pFVar1;
  undefined4 unaff_ESI;
  
  pFVar1 = operator_new(0x80);
  if (pFVar1 == (FlamePuffClass *)0x0) {
    pFVar1 = (FlamePuffClass *)0x0;
  }
  else {
    pFVar1 = FlamePuffClass(pFVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pFVar1;
}
