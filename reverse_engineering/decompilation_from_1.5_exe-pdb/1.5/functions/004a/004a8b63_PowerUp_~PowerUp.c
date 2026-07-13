/*
 * Entry: 004a8b63
 * Name: PowerUp::~PowerUp
 * Namespace: PowerUp
 * Signature: void ~PowerUp(PowerUp * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerUp::~PowerUp(PowerUp *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  GameObject::~GameObject((GameObject *)this);
  return;
}
