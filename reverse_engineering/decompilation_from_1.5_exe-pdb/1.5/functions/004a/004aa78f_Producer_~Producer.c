/*
 * Entry: 004aa78f
 * Name: Producer::~Producer
 * Namespace: Producer
 * Signature: void ~Producer(Producer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Producer::~Producer(Producer *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  HoverCraft::~HoverCraft((HoverCraft *)this);
  return;
}
