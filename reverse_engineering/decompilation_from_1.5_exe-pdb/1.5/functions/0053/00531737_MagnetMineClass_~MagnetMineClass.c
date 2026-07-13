/*
 * Entry: 00531737
 * Name: MagnetMineClass::~MagnetMineClass
 * Namespace: MagnetMineClass
 * Signature: void ~MagnetMineClass(MagnetMineClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MagnetMineClass::~MagnetMineClass(MagnetMineClass *this)

{
  this->_padding_ = (int)&_vftable_;
  MineClass::~MineClass((MineClass *)this);
  return;
}
