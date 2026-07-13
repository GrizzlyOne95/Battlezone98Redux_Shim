/*
 * Entry: 004ad1b4
 * Name: RepairDepotClass::RepairDepotClass
 * Namespace: RepairDepotClass
 * Signature: RepairDepotClass * RepairDepotClass(RepairDepotClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RepairDepotClass * __thiscall RepairDepotClass::RepairDepotClass(RepairDepotClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  this->repairRange = 30.0;
  this->repairDelay = 1.0;
  this->repairAmount = 100.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x52444550;
  this->_padding_ = (int)"repairdepot";
  this->_padding_ = 0x3c;
  this->_padding_ = 0x40;
  strncpy(this->repairSound,"repair.wav",0x10);
  return this;
}
