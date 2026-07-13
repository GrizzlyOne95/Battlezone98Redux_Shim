/*
 * Entry: 0053ab4d
 * Name: SprayBombClass::BuildClass
 * Namespace: SprayBombClass
 * Signature: OrdnanceClass * BuildClass(SprayBombClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall SprayBombClass::BuildClass(SprayBombClass *this,long64 param_1)

{
  SprayBombClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(200);
  if (pSVar1 == (SprayBombClass *)0x0) {
    pSVar1 = (SprayBombClass *)0x0;
  }
  else {
    pSVar1 = SprayBombClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pSVar1;
}
