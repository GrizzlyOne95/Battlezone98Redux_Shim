/*
 * Entry: 0046b40f
 * Name: WeaponCheck
 * Namespace: Global
 * Signature: ulong WeaponCheck(Craft * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl WeaponCheck(Craft *param_1)

{
  Carrier *this;
  uint uVar1;
  Weapon *pWVar2;
  int iVar3;
  ulong uVar4;
  
  this = (Carrier *)param_1->_padding_;
  uVar4 = 0;
  if (this != (Carrier *)0x0) {
    uVar1 = param_1->_padding_;
    iVar3 = 0;
    do {
      if ((uVar1 & 1 << ((byte)iVar3 & 0x1f)) != 0) {
        pWVar2 = Carrier::GetWeapon(this,iVar3);
        uVar4 = uVar4 * 2 ^ (uint)pWVar2;
        if (pWVar2 != (Weapon *)0x0) {
          uVar4 = uVar4 ^ pWVar2->weaponClass->sig ^ (uint)pWVar2->ordnanceClass;
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 5);
  }
  return uVar4;
}
