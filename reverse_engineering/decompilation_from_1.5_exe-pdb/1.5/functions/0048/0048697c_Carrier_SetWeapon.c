/*
 * Entry: 0048697c
 * Name: Carrier::SetWeapon
 * Namespace: Carrier
 * Signature: void SetWeapon(Carrier * this, int param_1, Weapon * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Carrier::SetWeapon(Carrier *this,int param_1,Weapon *param_2)

{
  if ((uint)param_1 < 5) {
    this->weapon[param_1] = param_2;
    if (param_2 == (Weapon *)0x0) {
      this->existant = this->existant & ~(1 << ((byte)param_1 & 0x1f));
    }
    else {
      this->existant = this->existant | 1 << ((byte)param_1 & 0x1f);
    }
  }
  return;
}
