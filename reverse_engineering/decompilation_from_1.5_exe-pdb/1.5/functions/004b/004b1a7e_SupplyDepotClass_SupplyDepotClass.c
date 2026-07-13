/*
 * Entry: 004b1a7e
 * Name: SupplyDepotClass::SupplyDepotClass
 * Namespace: SupplyDepotClass
 * Signature: SupplyDepotClass * SupplyDepotClass(SupplyDepotClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SupplyDepotClass * __thiscall SupplyDepotClass::SupplyDepotClass(SupplyDepotClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  this->supplyRange = 30.0;
  this->supplyDelay = 1.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x53444550;
  this->_padding_ = (int)"supplydepot";
  this->_padding_ = 0x41;
  this->_padding_ = 0x45;
  this->supplyAmount = 100;
  strncpy(this->supplySound,"weapon.wav",0x10);
  return this;
}
