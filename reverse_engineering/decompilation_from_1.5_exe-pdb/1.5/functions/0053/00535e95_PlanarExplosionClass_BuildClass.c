/*
 * Entry: 00535e95
 * Name: PlanarExplosionClass::BuildClass
 * Namespace: PlanarExplosionClass
 * Signature: ExplosionClass * BuildClass(PlanarExplosionClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass * __thiscall
PlanarExplosionClass::BuildClass(PlanarExplosionClass *this,long64 param_1)

{
  PlanarExplosionClass *this_00;
  ExplosionClass *pEVar1;
  undefined4 unaff_ESI;
  
  this_00 = operator_new(0x68);
  if (this_00 == (PlanarExplosionClass *)0x0) {
    pEVar1 = (ExplosionClass *)0x0;
  }
  else {
    pEVar1 = (ExplosionClass *)PlanarExplosionClass(this_00,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return pEVar1;
}
