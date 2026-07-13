/*
 * Entry: 004852e5
 * Name: ConstructionRig::~ConstructionRig
 * Namespace: ConstructionRig
 * Signature: void ~ConstructionRig(ConstructionRig * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ConstructionRig::~ConstructionRig(ConstructionRig *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Producer::~Producer((Producer *)this);
  return;
}
