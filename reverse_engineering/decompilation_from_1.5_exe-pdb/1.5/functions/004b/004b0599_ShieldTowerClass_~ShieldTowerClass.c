/*
 * Entry: 004b0599
 * Name: ShieldTowerClass::~ShieldTowerClass
 * Namespace: ShieldTowerClass
 * Signature: void ~ShieldTowerClass(ShieldTowerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShieldTowerClass::~ShieldTowerClass(ShieldTowerClass *this)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  return;
}
