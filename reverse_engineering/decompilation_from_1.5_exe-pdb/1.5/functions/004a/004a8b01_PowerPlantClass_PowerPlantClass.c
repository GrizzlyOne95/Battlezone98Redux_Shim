/*
 * Entry: 004a8b01
 * Name: PowerPlantClass::PowerPlantClass
 * Namespace: PowerPlantClass
 * Signature: PowerPlantClass * PowerPlantClass(PowerPlantClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerPlantClass * __thiscall PowerPlantClass::PowerPlantClass(PowerPlantClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  this->powerRadius = 100.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x504c4e54;
  this->_padding_ = (int)"powerplant";
  this->_padding_ = 0x2d;
  this->_padding_ = 0x36;
  return this;
}
