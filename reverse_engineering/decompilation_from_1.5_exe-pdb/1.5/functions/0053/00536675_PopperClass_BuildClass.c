/*
 * Entry: 00536675
 * Name: PopperClass::BuildClass
 * Namespace: PopperClass
 * Signature: OrdnanceClass * BuildClass(PopperClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall PopperClass::BuildClass(PopperClass *this,long64 param_1)

{
  PopperClass *pPVar1;
  undefined4 unaff_ESI;
  
  pPVar1 = operator_new(0xc0);
  if (pPVar1 == (PopperClass *)0x0) {
    pPVar1 = (PopperClass *)0x0;
  }
  else {
    pPVar1 = PopperClass(pPVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pPVar1;
}
