/*
 * Entry: 0053ba6b
 * Name: TargetingGunClass::Build
 * Namespace: TargetingGunClass
 * Signature: Weapon * Build(TargetingGunClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall TargetingGunClass::Build(TargetingGunClass *this,_OBJ76 *param_1)

{
  TargetingGun *pTVar1;
  
  pTVar1 = operator_new(200);
  if (pTVar1 == (TargetingGun *)0x0) {
    pTVar1 = (TargetingGun *)0x0;
  }
  else {
    pTVar1 = TargetingGun::TargetingGun(pTVar1,param_1,this);
  }
  return (Weapon *)pTVar1;
}
