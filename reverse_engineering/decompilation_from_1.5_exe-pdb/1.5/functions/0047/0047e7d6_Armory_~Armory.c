/*
 * Entry: 0047e7d6
 * Name: Armory::~Armory
 * Namespace: Armory
 * Signature: void ~Armory(Armory * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Armory::~Armory(Armory *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Producer::~Producer((Producer *)this);
  return;
}
