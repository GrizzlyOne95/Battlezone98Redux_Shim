/*
 * Entry: 00537143
 * Name: QuakeBlastClass::BuildClass
 * Namespace: QuakeBlastClass
 * Signature: ExplosionClass * BuildClass(QuakeBlastClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass * __thiscall QuakeBlastClass::BuildClass(QuakeBlastClass *this,long64 param_1)

{
  QuakeBlastClass *pQVar1;
  undefined4 unaff_ESI;
  
  pQVar1 = operator_new(0x70);
  if (pQVar1 == (QuakeBlastClass *)0x0) {
    pQVar1 = (QuakeBlastClass *)0x0;
  }
  else {
    pQVar1 = QuakeBlastClass(pQVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (ExplosionClass *)pQVar1;
}
