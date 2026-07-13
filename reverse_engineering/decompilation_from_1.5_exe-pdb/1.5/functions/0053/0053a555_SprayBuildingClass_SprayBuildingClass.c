/*
 * Entry: 0053a555
 * Name: SprayBuildingClass::SprayBuildingClass
 * Namespace: SprayBuildingClass
 * Signature: SprayBuildingClass * SprayBuildingClass(SprayBuildingClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SprayBuildingClass * __thiscall SprayBuildingClass::SprayBuildingClass(SprayBuildingClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  this->payloadClass = (OrdnanceClass *)0x0;
  this->shotDelay = 0.05;
  this->_padding_ = (int)&_vftable_;
  this->setAltitude = 2.0;
  this->_padding_ = 0x53424d42;
  this->_padding_ = (int)"spraybomb";
  this->omegaSpin = 10.0;
  this->_padding_ = 5;
  this->fireSound[0] = '\0';
  this->anglePitch = 0.25;
  return this;
}
