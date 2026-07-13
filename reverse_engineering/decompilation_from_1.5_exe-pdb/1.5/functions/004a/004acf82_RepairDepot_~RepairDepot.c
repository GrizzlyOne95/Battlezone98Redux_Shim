/*
 * Entry: 004acf82
 * Name: RepairDepot::~RepairDepot
 * Namespace: RepairDepot
 * Signature: void ~RepairDepot(RepairDepot * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RepairDepot::~RepairDepot(RepairDepot *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Building::~Building((Building *)this);
  return;
}
