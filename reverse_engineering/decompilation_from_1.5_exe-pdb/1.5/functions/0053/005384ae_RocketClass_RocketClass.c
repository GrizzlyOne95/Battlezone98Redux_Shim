/*
 * Entry: 005384ae
 * Name: RocketClass::RocketClass
 * Namespace: RocketClass
 * Signature: RocketClass * RocketClass(RocketClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RocketClass * __thiscall RocketClass::RocketClass(RocketClass *this)

{
  BulletClass::BulletClass((BulletClass *)this);
  this->flameRadius = 0.0;
  this->flameLength = 0.0;
  this->flameIndex = 0;
  this->flareRadius = 0.0;
  this->flameCount = 0;
  this->flareIndex = 0;
  this->smokeDevRadial = 0.5;
  this->flareCount = 0;
  this->smokeIndex = 0;
  this->smokeDevAxial = 0.2;
  this->smokeCount = 0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x52434b54;
  this->smokeInherit = 0.0;
  this->_padding_ = (int)"rocket";
  this->smokeRadius = 0.3;
  this->smokeRate = 5.0;
  this->smokePause = 0.3 / (float)this->_padding_;
  return this;
}
