/*
 * Entry: 0045f8b7
 * Name: GiveWeapon
 * Namespace: Global
 * Signature: bool GiveWeapon(int param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl GiveWeapon(int param_1,char *param_2,int param_3)

{
  bool bVar1;
  GameObject *pGVar2;
  WeaponClass *pWVar3;
  
  pGVar2 = GameObjectHandle::GetObj(param_1);
  if (pGVar2 == (GameObject *)0x0) {
    return false;
  }
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    pWVar3 = (WeaponClass *)0x0;
  }
  else {
    pWVar3 = WeaponClass::Find(param_2);
  }
  bVar1 = WeaponPowerup::GiveWeapon(pGVar2,pWVar3,param_3);
  return bVar1;
}
