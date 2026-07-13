/*
 * Entry: 004b92e7
 * Name: WeaponPowerup::GiveWeapon
 * Namespace: WeaponPowerup
 * Signature: bool GiveWeapon(GameObject * param_1, WeaponClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl WeaponPowerup::GiveWeapon(GameObject *param_1,WeaponClass *param_2)

{
  Carrier *this;
  _OBJ76 *p_Var1;
  Carrier *pCVar2;
  bool bVar3;
  Weapon *pWVar4;
  long lVar5;
  int iVar6;
  int local_c;
  int local_8;
  
  iVar6 = 0;
  local_c = 0x7fffffff;
  local_8 = 5;
  if (((param_1 != (GameObject *)0x0) && (param_2 != (WeaponClass *)0x0)) &&
     (this = param_1->carrier, pCVar2 = this, this != (Carrier *)0x0)) {
    do {
      p_Var1 = pCVar2->hardpoint[0];
      if ((p_Var1 != (_OBJ76 *)0x0) &&
         ((param_2->wpnCategory == CLASS_ID_WEAPON_HARDPOINT ||
          (param_2->wpnCategory == p_Var1->class_id)))) {
        pWVar4 = Carrier::GetWeapon(this,iVar6);
        if (pWVar4 == (Weapon *)0x0) {
          lVar5 = -0x80000000;
        }
        else if (pWVar4->weaponClass == param_2) {
          lVar5 = 0x7fffffff;
        }
        else {
          lVar5 = pWVar4->weaponClass->wpnPriority;
        }
        if (lVar5 < local_c) {
          local_c = lVar5;
          local_8 = iVar6;
        }
      }
      iVar6 = iVar6 + 1;
      pCVar2 = (Carrier *)pCVar2->hardpoint;
    } while (iVar6 < 5);
    if (local_8 < 5) {
      bVar3 = GiveWeapon(param_1,param_2,local_8);
      return bVar3;
    }
  }
  return false;
}
