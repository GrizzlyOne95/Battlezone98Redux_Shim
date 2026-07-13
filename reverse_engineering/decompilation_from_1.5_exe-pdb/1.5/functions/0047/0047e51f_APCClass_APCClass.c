/*
 * Entry: 0047e51f
 * Name: APCClass::APCClass
 * Namespace: APCClass
 * Signature: APCClass * APCClass(APCClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

APCClass * __thiscall APCClass::APCClass(APCClass *this)

{
  HoverCraftClass::HoverCraftClass((HoverCraftClass *)this);
  this->soldierDelay = 0.0;
  this->reloadDelay = 0.2;
  this->_padding_ = (int)&_vftable_;
  this->soldierClass = (GameObjectClass *)0x40a00000;
  this->_padding_ = 0x41504300;
  this->soldierCount = 0x40a00000;
  this->_padding_ = (int)"apc";
  this->_padding_ = 5;
  this->reloadReset = 50.0;
  this->_padding_ = 0xe;
  this->reloadRange = 1.4013e-45;
  this[1]._padding_ = 0;
  this[1]._padding_ = 0x40a00000;
  return this;
}
