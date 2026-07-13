/*
 * Entry: 00535e23
 * Name: OrdnanceClass::BuildClass
 * Namespace: OrdnanceClass
 * Signature: OrdnanceClass * BuildClass(OrdnanceClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall OrdnanceClass::BuildClass(OrdnanceClass *this,long64 param_1)

{
  OrdnanceClass *pOVar1;
  undefined4 unaff_ESI;
  
  pOVar1 = operator_new(0x70);
  if (pOVar1 == (OrdnanceClass *)0x0) {
    pOVar1 = (OrdnanceClass *)0x0;
  }
  else {
    pOVar1 = OrdnanceClass(pOVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return pOVar1;
}
