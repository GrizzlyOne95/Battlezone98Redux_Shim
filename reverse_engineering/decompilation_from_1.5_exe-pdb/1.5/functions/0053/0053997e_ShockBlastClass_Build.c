/*
 * Entry: 0053997e
 * Name: ShockBlastClass::Build
 * Namespace: ShockBlastClass
 * Signature: Explosion * Build(ShockBlastClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Explosion * __thiscall ShockBlastClass::Build(ShockBlastClass *this,_OBJ76 *param_1)

{
  ShockBlast *this_00;
  Explosion *pEVar1;
  
  this_00 = operator_new(0x38);
  if (this_00 == (ShockBlast *)0x0) {
    pEVar1 = (Explosion *)0x0;
  }
  else {
    pEVar1 = (Explosion *)ShockBlast::ShockBlast(this_00,param_1,this);
  }
  return pEVar1;
}
