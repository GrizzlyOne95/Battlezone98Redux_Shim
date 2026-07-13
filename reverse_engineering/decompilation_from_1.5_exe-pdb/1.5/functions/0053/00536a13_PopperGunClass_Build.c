/*
 * Entry: 00536a13
 * Name: PopperGunClass::Build
 * Namespace: PopperGunClass
 * Signature: Weapon * Build(PopperGunClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall PopperGunClass::Build(PopperGunClass *this,_OBJ76 *param_1)

{
  PopperGun *pPVar1;
  
  pPVar1 = operator_new(0xb8);
  if (pPVar1 == (PopperGun *)0x0) {
    pPVar1 = (PopperGun *)0x0;
  }
  else {
    pPVar1 = PopperGun::PopperGun(pPVar1,param_1,this);
  }
  return (Weapon *)pPVar1;
}
