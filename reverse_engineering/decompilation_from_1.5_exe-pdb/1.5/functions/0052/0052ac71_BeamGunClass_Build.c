/*
 * Entry: 0052ac71
 * Name: BeamGunClass::Build
 * Namespace: BeamGunClass
 * Signature: Weapon * Build(BeamGunClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall BeamGunClass::Build(BeamGunClass *this,_OBJ76 *param_1)

{
  BeamGun *pBVar1;
  
  pBVar1 = operator_new(0xc0);
  if (pBVar1 == (BeamGun *)0x0) {
    pBVar1 = (BeamGun *)0x0;
  }
  else {
    pBVar1 = BeamGun::BeamGun(pBVar1,param_1,this);
  }
  return (Weapon *)pBVar1;
}
