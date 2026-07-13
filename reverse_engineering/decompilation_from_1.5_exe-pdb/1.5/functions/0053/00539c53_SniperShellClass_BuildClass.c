/*
 * Entry: 00539c53
 * Name: SniperShellClass::BuildClass
 * Namespace: SniperShellClass
 * Signature: OrdnanceClass * BuildClass(SniperShellClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall SniperShellClass::BuildClass(SniperShellClass *this,long64 param_1)

{
  SniperShellClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0x78);
  if (pSVar1 == (SniperShellClass *)0x0) {
    pSVar1 = (SniperShellClass *)0x0;
  }
  else {
    pSVar1 = SniperShellClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pSVar1;
}
