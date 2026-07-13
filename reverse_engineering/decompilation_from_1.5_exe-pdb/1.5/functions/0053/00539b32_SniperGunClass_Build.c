/*
 * Entry: 00539b32
 * Name: SniperGunClass::Build
 * Namespace: SniperGunClass
 * Signature: Weapon * Build(SniperGunClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall SniperGunClass::Build(SniperGunClass *this,_OBJ76 *param_1)

{
  SniperGun *pSVar1;
  
  pSVar1 = operator_new(0xb8);
  if (pSVar1 == (SniperGun *)0x0) {
    pSVar1 = (SniperGun *)0x0;
  }
  else {
    pSVar1 = SniperGun::SniperGun(pSVar1,param_1,this);
  }
  return (Weapon *)pSVar1;
}
