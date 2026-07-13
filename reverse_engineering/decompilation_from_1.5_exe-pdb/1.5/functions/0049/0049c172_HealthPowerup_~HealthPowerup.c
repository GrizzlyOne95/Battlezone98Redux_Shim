/*
 * Entry: 0049c172
 * Name: HealthPowerup::~HealthPowerup
 * Namespace: HealthPowerup
 * Signature: void ~HealthPowerup(HealthPowerup * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HealthPowerup::~HealthPowerup(HealthPowerup *this)

{
  *(undefined ***)this = &PowerUp::_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &PowerUp::_vftable__for__DistributedObject__;
  GameObject::~GameObject((GameObject *)this);
  return;
}
