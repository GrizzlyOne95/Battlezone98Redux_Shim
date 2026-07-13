/*
 * Entry: 00531eb6
 * Name: MineClass::MineClass
 * Namespace: MineClass
 * Signature: MineClass * MineClass(MineClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MineClass * __thiscall MineClass::MineClass(MineClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  this->lifeSpan = 300.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x4d494e45;
  this->_padding_ = (int)"mine";
  this->_padding_ = 5;
  this->_padding_ = 0x96;
  return this;
}
