/*
 * Entry: 0049503f
 * Name: Carrier::Carrier
 * Namespace: Carrier
 * Signature: Carrier * Carrier(Carrier * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Carrier * __thiscall Carrier::Carrier(Carrier *this,GameObject *param_1)

{
  Weapon **ppWVar1;
  int iVar2;
  
  this->owner = param_1;
  ppWVar1 = this->weapon;
  iVar2 = 5;
  do {
    ppWVar1[-5] = (Weapon *)0x0;
    *ppWVar1 = (Weapon *)0x0;
    ppWVar1 = ppWVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  this->special = -1;
  this->existant = 0;
  this->enabled = 0;
  this->selected = 0;
  return this;
}
