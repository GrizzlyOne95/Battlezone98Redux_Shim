/*
 * Entry: 0052f655
 * Name: ExplosionClass::BuildClass
 * Namespace: ExplosionClass
 * Signature: ExplosionClass * BuildClass(ExplosionClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass * __thiscall ExplosionClass::BuildClass(ExplosionClass *this,long64 param_1)

{
  ExplosionClass *pEVar1;
  undefined4 unaff_ESI;
  
  pEVar1 = operator_new(0x68);
  if (pEVar1 == (ExplosionClass *)0x0) {
    pEVar1 = (ExplosionClass *)0x0;
  }
  else {
    pEVar1 = ExplosionClass(pEVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return pEVar1;
}
