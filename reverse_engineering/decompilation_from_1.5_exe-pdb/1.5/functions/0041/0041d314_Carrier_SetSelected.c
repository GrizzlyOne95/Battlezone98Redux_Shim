/*
 * Entry: 0041d314
 * Name: Carrier::SetSelected
 * Namespace: Carrier
 * Signature: void SetSelected(Carrier * this, ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Carrier::SetSelected(Carrier *this,ulong param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  Weapon **ppWVar4;
  int iVar5;
  
  uVar2 = param_1 & this->existant;
  uVar1 = this->selected;
  this->selected = uVar2;
  iVar5 = 0;
  ppWVar4 = this->weapon;
  do {
    uVar3 = 1 << ((byte)iVar5 & 0x1f);
    if ((~uVar1 & uVar2 & uVar3) == 0) {
      if ((~uVar2 & uVar1 & uVar3) != 0) {
        (**(code **)((*ppWVar4)->_padding_ + 0x20))();
      }
    }
    else {
      (**(code **)((*ppWVar4)->_padding_ + 0x1c))();
    }
    iVar5 = iVar5 + 1;
    ppWVar4 = ppWVar4 + 1;
  } while (iVar5 < 5);
  return;
}
