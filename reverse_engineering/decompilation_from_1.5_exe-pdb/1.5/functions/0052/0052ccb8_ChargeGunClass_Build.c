/*
 * Entry: 0052ccb8
 * Name: ChargeGunClass::Build
 * Namespace: ChargeGunClass
 * Signature: Weapon * Build(ChargeGunClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall ChargeGunClass::Build(ChargeGunClass *this,_OBJ76 *param_1)

{
  ChargeGun *pCVar1;
  
  pCVar1 = operator_new(0xd0);
  if (pCVar1 == (ChargeGun *)0x0) {
    pCVar1 = (ChargeGun *)0x0;
  }
  else {
    pCVar1 = ChargeGun::ChargeGun(pCVar1,param_1,this);
  }
  return (Weapon *)pCVar1;
}
