/*
 * Entry: 0052ffbb
 * Name: GrenadeClass::BuildClass
 * Namespace: GrenadeClass
 * Signature: OrdnanceClass * BuildClass(GrenadeClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall GrenadeClass::BuildClass(GrenadeClass *this,long64 param_1)

{
  GrenadeClass *pGVar1;
  undefined4 unaff_ESI;
  
  pGVar1 = operator_new(0xb0);
  if (pGVar1 == (GrenadeClass *)0x0) {
    pGVar1 = (GrenadeClass *)0x0;
  }
  else {
    pGVar1 = GrenadeClass(pGVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pGVar1;
}
