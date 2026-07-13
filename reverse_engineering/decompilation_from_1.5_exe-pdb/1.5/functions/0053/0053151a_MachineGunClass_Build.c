/*
 * Entry: 0053151a
 * Name: MachineGunClass::Build
 * Namespace: MachineGunClass
 * Signature: Weapon * Build(MachineGunClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall MachineGunClass::Build(MachineGunClass *this,_OBJ76 *param_1)

{
  MachineGun *pMVar1;
  
  pMVar1 = operator_new(0xc0);
  if (pMVar1 == (MachineGun *)0x0) {
    pMVar1 = (MachineGun *)0x0;
  }
  else {
    pMVar1 = MachineGun::MachineGun(pMVar1,param_1,this);
  }
  return (Weapon *)pMVar1;
}
