/*
 * Entry: 00529c1c
 * Name: AnchorRocketClass::BuildClass
 * Namespace: AnchorRocketClass
 * Signature: OrdnanceClass * BuildClass(AnchorRocketClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall AnchorRocketClass::BuildClass(AnchorRocketClass *this,long64 param_1)

{
  AnchorRocketClass *pAVar1;
  undefined4 unaff_ESI;
  
  pAVar1 = operator_new(0xc0);
  if (pAVar1 == (AnchorRocketClass *)0x0) {
    pAVar1 = (AnchorRocketClass *)0x0;
  }
  else {
    pAVar1 = AnchorRocketClass(pAVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pAVar1;
}
