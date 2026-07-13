/*
 * Entry: 0053990e
 * Name: ShockBlastClass::BuildClass
 * Namespace: ShockBlastClass
 * Signature: ExplosionClass * BuildClass(ShockBlastClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass * __thiscall ShockBlastClass::BuildClass(ShockBlastClass *this,long64 param_1)

{
  ShockBlastClass *this_00;
  ExplosionClass *pEVar1;
  undefined4 unaff_ESI;
  
  this_00 = operator_new(0x68);
  if (this_00 == (ShockBlastClass *)0x0) {
    pEVar1 = (ExplosionClass *)0x0;
  }
  else {
    pEVar1 = (ExplosionClass *)ShockBlastClass(this_00,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return pEVar1;
}
