/*
 * Entry: 00538546
 * Name: RocketClass::Build
 * Namespace: RocketClass
 * Signature: Ordnance * Build(RocketClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall RocketClass::Build(RocketClass *this,_OBJ76 *param_1)

{
  Rocket *pRVar1;
  
  pRVar1 = operator_new(0xe8);
  if (pRVar1 == (Rocket *)0x0) {
    pRVar1 = (Rocket *)0x0;
  }
  else {
    pRVar1 = Rocket::Rocket(pRVar1,param_1,this);
  }
  return (Ordnance *)pRVar1;
}
