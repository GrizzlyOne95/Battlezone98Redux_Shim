/*
 * Entry: 004b184c
 * Name: SupplyDepot::~SupplyDepot
 * Namespace: SupplyDepot
 * Signature: void ~SupplyDepot(SupplyDepot * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SupplyDepot::~SupplyDepot(SupplyDepot *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Building::~Building((Building *)this);
  return;
}
