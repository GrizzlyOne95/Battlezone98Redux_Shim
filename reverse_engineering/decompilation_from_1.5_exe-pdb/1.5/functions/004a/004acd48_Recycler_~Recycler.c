/*
 * Entry: 004acd48
 * Name: Recycler::~Recycler
 * Namespace: Recycler
 * Signature: void ~Recycler(Recycler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Recycler::~Recycler(Recycler *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Producer::~Producer((Producer *)this);
  return;
}
