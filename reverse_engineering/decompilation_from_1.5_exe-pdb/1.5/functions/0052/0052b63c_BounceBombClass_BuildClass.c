/*
 * Entry: 0052b63c
 * Name: BounceBombClass::BuildClass
 * Namespace: BounceBombClass
 * Signature: OrdnanceClass * BuildClass(BounceBombClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall BounceBombClass::BuildClass(BounceBombClass *this,long64 param_1)

{
  BounceBombClass *pBVar1;
  undefined4 unaff_ESI;
  
  pBVar1 = operator_new(200);
  if (pBVar1 == (BounceBombClass *)0x0) {
    pBVar1 = (BounceBombClass *)0x0;
  }
  else {
    pBVar1 = BounceBombClass(pBVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pBVar1;
}
