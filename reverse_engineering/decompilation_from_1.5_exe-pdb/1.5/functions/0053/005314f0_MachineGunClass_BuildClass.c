/*
 * Entry: 005314f0
 * Name: MachineGunClass::BuildClass
 * Namespace: MachineGunClass
 * Signature: WeaponClass * BuildClass(MachineGunClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall MachineGunClass::BuildClass(MachineGunClass *this,long64 param_1)

{
  MachineGunClass *pMVar1;
  undefined4 unaff_ESI;
  
  pMVar1 = operator_new(0x80);
  if (pMVar1 == (MachineGunClass *)0x0) {
    pMVar1 = (MachineGunClass *)0x0;
  }
  else {
    pMVar1 = MachineGunClass(pMVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pMVar1;
}
