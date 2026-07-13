/*
 * Entry: 0047bcc4
 * Name: AmmoPowerup::~AmmoPowerup
 * Namespace: AmmoPowerup
 * Signature: void ~AmmoPowerup(AmmoPowerup * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AmmoPowerup::~AmmoPowerup(AmmoPowerup *this)

{
  *(undefined ***)this = &PowerUp::_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &PowerUp::_vftable__for__DistributedObject__;
  GameObject::~GameObject((GameObject *)this);
  return;
}
