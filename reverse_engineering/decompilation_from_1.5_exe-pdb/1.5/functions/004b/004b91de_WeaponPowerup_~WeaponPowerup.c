/*
 * Entry: 004b91de
 * Name: WeaponPowerup::~WeaponPowerup
 * Namespace: WeaponPowerup
 * Signature: void ~WeaponPowerup(WeaponPowerup * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WeaponPowerup::~WeaponPowerup(WeaponPowerup *this)

{
  *(undefined ***)this = &PowerUp::_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &PowerUp::_vftable__for__DistributedObject__;
  GameObject::~GameObject((GameObject *)this);
  return;
}
