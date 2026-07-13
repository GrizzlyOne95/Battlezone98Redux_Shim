/*
 * Entry: 00485201
 * Name: CommTowerClass::CommTowerClass
 * Namespace: CommTowerClass
 * Signature: CommTowerClass * CommTowerClass(CommTowerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CommTowerClass * __thiscall CommTowerClass::CommTowerClass(CommTowerClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  this->rangeScan = 500.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x434f4d4d;
  this->periodScan = 0.0;
  this->_padding_ = (int)"commtower";
  this->_padding_ = 0x37;
  this->_padding_ = 0x3b;
  return this;
}
