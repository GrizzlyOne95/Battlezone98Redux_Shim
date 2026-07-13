/*
 * Entry: 0041d365
 * Name: Carrier::TriggerSelected
 * Namespace: Carrier
 * Signature: void TriggerSelected(Carrier * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Carrier::TriggerSelected(Carrier *this)

{
  int iVar1;
  Weapon **ppWVar2;
  float fVar3;
  
  fVar3 = Get_Time();
  iVar1 = 0;
  ppWVar2 = this->weapon;
  this->fWeaponTriggerTillTime = fVar3 + Net::fWeaponTriggerHoldTime;
  do {
    if ((this->enabled & 1 << ((byte)iVar1 & 0x1f) & this->selected) != 0) {
      (**(code **)((*ppWVar2)->_padding_ + 8))();
    }
    iVar1 = iVar1 + 1;
    ppWVar2 = ppWVar2 + 1;
  } while (iVar1 < 5);
  return;
}
