/*
 * Entry: 00536bca
 * Name: ProximityMine::~ProximityMine
 * Namespace: ProximityMine
 * Signature: void ~ProximityMine(ProximityMine * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ProximityMine::~ProximityMine(ProximityMine *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Mine::~Mine((Mine *)this);
  return;
}
