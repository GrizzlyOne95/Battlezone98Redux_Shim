/*
 * Entry: 0052a165
 * Name: BeamClass::BuildClass
 * Namespace: BeamClass
 * Signature: OrdnanceClass * BuildClass(BeamClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall BeamClass::BuildClass(BeamClass *this,long64 param_1)

{
  BeamClass *pBVar1;
  undefined4 unaff_ESI;
  
  pBVar1 = operator_new(0x80);
  if (pBVar1 == (BeamClass *)0x0) {
    pBVar1 = (BeamClass *)0x0;
  }
  else {
    pBVar1 = BeamClass(pBVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pBVar1;
}
