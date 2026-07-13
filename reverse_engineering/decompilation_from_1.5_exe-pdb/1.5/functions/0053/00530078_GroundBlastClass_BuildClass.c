/*
 * Entry: 00530078
 * Name: GroundBlastClass::BuildClass
 * Namespace: GroundBlastClass
 * Signature: ExplosionClass * BuildClass(GroundBlastClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass * __thiscall GroundBlastClass::BuildClass(GroundBlastClass *this,long64 param_1)

{
  GroundBlastClass *this_00;
  ExplosionClass *pEVar1;
  undefined4 unaff_ESI;
  
  this_00 = operator_new(0x68);
  if (this_00 == (GroundBlastClass *)0x0) {
    pEVar1 = (ExplosionClass *)0x0;
  }
  else {
    pEVar1 = (ExplosionClass *)GroundBlastClass(this_00,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return pEVar1;
}
