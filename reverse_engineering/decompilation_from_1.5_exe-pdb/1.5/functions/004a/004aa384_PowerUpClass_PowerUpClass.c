/*
 * Entry: 004aa384
 * Name: PowerUpClass::PowerUpClass
 * Namespace: PowerUpClass
 * Signature: PowerUpClass * PowerUpClass(PowerUpClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerUpClass * __thiscall PowerUpClass::PowerUpClass(PowerUpClass *this)

{
  GameObjectClass::GameObjectClass((GameObjectClass *)this);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x50575550;
  this->_padding_ = (int)"powerup";
  this->_padding_ = 3;
  this->soundPickup[0] = '\0';
  this->soundReject[0] = '\0';
  return this;
}
