/*
 * Entry: 00482998
 * Name: BarracksClass::BarracksClass
 * Namespace: BarracksClass
 * Signature: BarracksClass * BarracksClass(BarracksClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BarracksClass * __thiscall BarracksClass::BarracksClass(BarracksClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  this->pilotClass = (GameObjectClass *)0x0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x42415252;
  this->_padding_ = (int)"barracks";
  this->_padding_ = 0x4b;
  this->_padding_ = 0x4f;
  this->pilotHold = 10;
  return this;
}
