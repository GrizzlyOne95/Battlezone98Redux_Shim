/*
 * Entry: 0045f87b
 * Name: GiveWeapon
 * Namespace: Global
 * Signature: bool GiveWeapon(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl GiveWeapon(int param_1,char *param_2)

{
  bool bVar1;
  GameObject *pGVar2;
  WeaponClass *pWVar3;
  
  pGVar2 = GameObjectHandle::GetObj(param_1);
  if (pGVar2 != (GameObject *)0x0) {
    if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
      pWVar3 = (WeaponClass *)0x0;
    }
    else {
      pWVar3 = WeaponClass::Find(param_2);
    }
    if (pWVar3 != (WeaponClass *)0x0) {
      bVar1 = WeaponPowerup::GiveWeapon(pGVar2,pWVar3);
      return bVar1;
    }
  }
  return false;
}
