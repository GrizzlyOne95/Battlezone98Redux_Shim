/*
 * Entry: 0053db39
 * Name: TracerClass::BuildClass
 * Namespace: TracerClass
 * Signature: OrdnanceClass * BuildClass(TracerClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall TracerClass::BuildClass(TracerClass *this,long64 param_1)

{
  TracerClass *pTVar1;
  undefined4 unaff_ESI;
  
  pTVar1 = operator_new(0x88);
  if (pTVar1 == (TracerClass *)0x0) {
    pTVar1 = (TracerClass *)0x0;
  }
  else {
    pTVar1 = TracerClass(pTVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pTVar1;
}
