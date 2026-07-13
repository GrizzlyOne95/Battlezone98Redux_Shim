/*
 * Entry: 004ae72c
 * Name: Scavenger::~Scavenger
 * Namespace: Scavenger
 * Signature: void ~Scavenger(Scavenger * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scavenger::~Scavenger(Scavenger *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  HoverCraft::~HoverCraft((HoverCraft *)this);
  return;
}
