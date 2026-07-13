/*
 * Entry: 004b05f4
 * Name: ShieldTowerClass::ShieldTowerClass
 * Namespace: ShieldTowerClass
 * Signature: ShieldTowerClass * ShieldTowerClass(ShieldTowerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ShieldTowerClass * __thiscall ShieldTowerClass::ShieldTowerClass(ShieldTowerClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  (this->shieldBox).min.x = -50.0;
  this->_padding_ = -1;
  this->_padding_ = -1;
  (this->shieldBox).min.y = 0.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x53484c44;
  (this->shieldBox).min.z = -5.0;
  this->_padding_ = (int)"shieldtower";
  (this->shieldBox).max.x = 50.0;
  (this->shieldBox).max.y = 10.0;
  (this->shieldBox).max.z = 5.0;
  this->objPush = 100.0;
  this->objDrag = 1.0;
  this->ordPush = 200.0;
  this->ordDrag = 3.0;
  return this;
}
