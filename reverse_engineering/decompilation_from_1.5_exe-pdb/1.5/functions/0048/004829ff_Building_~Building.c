/*
 * Entry: 004829ff
 * Name: Building::~Building
 * Namespace: Building
 * Signature: void ~Building(Building * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Building::~Building(Building *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  GameObject::~GameObject((GameObject *)this);
  return;
}
