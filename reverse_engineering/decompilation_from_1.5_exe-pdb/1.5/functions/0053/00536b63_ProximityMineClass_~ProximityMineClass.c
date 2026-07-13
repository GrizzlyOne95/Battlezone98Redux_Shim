/*
 * Entry: 00536b63
 * Name: ProximityMineClass::~ProximityMineClass
 * Namespace: ProximityMineClass
 * Signature: void ~ProximityMineClass(ProximityMineClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ProximityMineClass::~ProximityMineClass(ProximityMineClass *this)

{
  this->_padding_ = (int)&_vftable_;
  MineClass::~MineClass((MineClass *)this);
  return;
}
