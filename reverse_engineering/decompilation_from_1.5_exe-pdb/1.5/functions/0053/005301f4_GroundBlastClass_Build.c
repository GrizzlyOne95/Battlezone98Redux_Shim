/*
 * Entry: 005301f4
 * Name: GroundBlastClass::Build
 * Namespace: GroundBlastClass
 * Signature: Explosion * Build(GroundBlastClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Explosion * __thiscall GroundBlastClass::Build(GroundBlastClass *this,_OBJ76 *param_1)

{
  GroundBlast *this_00;
  Explosion *pEVar1;
  
  this_00 = operator_new(0x38);
  if (this_00 == (GroundBlast *)0x0) {
    pEVar1 = (Explosion *)0x0;
  }
  else {
    pEVar1 = (Explosion *)GroundBlast::GroundBlast(this_00,param_1,this);
  }
  return pEVar1;
}
