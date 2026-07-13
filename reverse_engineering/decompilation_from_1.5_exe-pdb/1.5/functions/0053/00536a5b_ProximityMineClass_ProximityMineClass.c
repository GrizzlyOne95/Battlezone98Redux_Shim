/*
 * Entry: 00536a5b
 * Name: ProximityMineClass::ProximityMineClass
 * Namespace: ProximityMineClass
 * Signature: ProximityMineClass * ProximityMineClass(ProximityMineClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ProximityMineClass * __thiscall ProximityMineClass::ProximityMineClass(ProximityMineClass *this)

{
  MineClass::MineClass((MineClass *)this);
  this->xplClass = (ExplosionClass *)0x0;
  this->_padding_ = 0x7149f2ca;
  this->_padding_ = (int)&_vftable_;
  this->searchRadius = 20.0;
  this->_padding_ = 0x50524f58;
  this->_padding_ = (int)"proximity";
  this->searchPeriod = 0.1;
  this->_padding_ = 0x96;
  return this;
}
