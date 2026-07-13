/*
 * Entry: 004059d0
 * Name: Carrier::GetWeapon
 * Namespace: Carrier
 * Signature: Weapon * GetWeapon(Carrier * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall Carrier::GetWeapon(Carrier *this,int param_1)

{
  Weapon *pWVar1;
  
  if ((this->existant & 1 << ((byte)param_1 & 0x1f)) == 0) {
    pWVar1 = (Weapon *)0x0;
  }
  else {
    pWVar1 = this->weapon[param_1];
  }
  return pWVar1;
}
