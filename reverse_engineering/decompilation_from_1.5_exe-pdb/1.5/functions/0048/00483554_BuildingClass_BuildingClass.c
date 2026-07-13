/*
 * Entry: 00483554
 * Name: BuildingClass::BuildingClass
 * Namespace: BuildingClass
 * Signature: BuildingClass * BuildingClass(BuildingClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BuildingClass * __thiscall BuildingClass::BuildingClass(BuildingClass *this)

{
  GameObjectClass::GameObjectClass((GameObjectClass *)this);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x424c4447;
  this->_padding_ = (int)"i76building";
  this->_padding_ = 2;
  this->soundAmbient[0] = '\0';
  return this;
}
