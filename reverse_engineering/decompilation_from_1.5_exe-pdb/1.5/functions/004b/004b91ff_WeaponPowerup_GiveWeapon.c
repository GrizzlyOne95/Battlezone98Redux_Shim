/*
 * Entry: 004b91ff
 * Name: WeaponPowerup::GiveWeapon
 * Namespace: WeaponPowerup
 * Signature: bool GiveWeapon(GameObject * param_1, WeaponClass * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl WeaponPowerup::GiveWeapon(GameObject *param_1,WeaponClass *param_2,int param_3)

{
  Carrier *this;
  UserProcess *this_00;
  bool bVar1;
  Weapon *pWVar2;
  _OBJ76 *p_Var3;
  uint uVar4;
  byte bVar5;
  _OBJ76 *p_Var6;
  
  if (param_1 == (GameObject *)0x0) {
    bVar1 = false;
  }
  else if ((param_3 < 0) && (4 < param_3)) {
    bVar1 = false;
  }
  else {
    this = param_1->carrier;
    if ((this == (Carrier *)0x0) || (p_Var6 = this->hardpoint[param_3], p_Var6 == (_OBJ76 *)0x0)) {
      bVar1 = false;
    }
    else {
      pWVar2 = Carrier::GetWeapon(this,param_3);
      bVar5 = (byte)param_3;
      if (pWVar2 != (Weapon *)0x0) {
        if ((uint)param_3 < 5) {
          this->weapon[param_3] = (Weapon *)0x0;
          this->existant = this->existant & ~(1 << (bVar5 & 0x1f));
        }
        Weapon::Remove(pWVar2);
      }
      if (param_2 == (WeaponClass *)0x0) {
        uVar4 = ~(1 << (bVar5 & 0x1f));
        this->enabled = this->enabled & this->existant & uVar4;
        param_1->weaponMask = param_1->weaponMask & uVar4;
      }
      else {
        p_Var3 = (_OBJ76 *)(**(code **)(param_1->_padding_ + 0x30))();
        pWVar2 = WeaponClass::Build(param_2,p_Var3,p_Var6);
        Carrier::SetWeapon(this,param_3,pWVar2);
        uVar4 = 1 << (bVar5 & 0x1f);
        this->enabled = (this->enabled | uVar4) & this->existant;
        param_1->weaponMask = param_1->weaponMask | uVar4;
      }
      this_00 = (UserProcess *)param_1->aiProcess;
      if ((this_00 != (UserProcess *)0x0) &&
         (bVar1 = SObject::IsKindOf((SObject *)this_00,&UserProcess::classUserProcess), bVar1)) {
        UserProcess::Init(this_00);
      }
      bVar1 = true;
    }
  }
  return bVar1;
}
