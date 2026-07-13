/*
 * Entry: 004aa3b9
 * Name: PowerUpClass::~PowerUpClass
 * Namespace: PowerUpClass
 * Signature: void ~PowerUpClass(PowerUpClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerUpClass::~PowerUpClass(PowerUpClass *this)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  return;
}
