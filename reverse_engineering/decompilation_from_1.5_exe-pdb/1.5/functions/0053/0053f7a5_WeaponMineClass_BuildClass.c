/*
 * Entry: 0053f7a5
 * Name: WeaponMineClass::BuildClass
 * Namespace: WeaponMineClass
 * Signature: GameObjectClass * BuildClass(WeaponMineClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall WeaponMineClass::BuildClass(WeaponMineClass *this,long64 param_1)

{
  WeaponMineClass *pWVar1;
  undefined4 unaff_ESI;
  
  pWVar1 = operator_new(0x178);
  if (pWVar1 == (WeaponMineClass *)0x0) {
    pWVar1 = (WeaponMineClass *)0x0;
  }
  else {
    pWVar1 = WeaponMineClass(pWVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pWVar1;
}
