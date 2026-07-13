/*
 * Entry: 004869aa
 * Name: Carrier::UnTriggerAll
 * Namespace: Carrier
 * Signature: void UnTriggerAll(Carrier * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Carrier::UnTriggerAll(Carrier *this)

{
  Weapon **ppWVar1;
  int iVar2;
  
  ppWVar1 = this->weapon;
  iVar2 = 5;
  do {
    if (*ppWVar1 != (Weapon *)0x0) {
      (**(code **)((*ppWVar1)->_padding_ + 0xc))();
    }
    ppWVar1 = ppWVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}
