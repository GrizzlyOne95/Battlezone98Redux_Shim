/*
 * Entry: 004ad946
 * Name: SAVClass::SAVClass
 * Namespace: SAVClass
 * Signature: SAVClass * SAVClass(SAVClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SAVClass * __thiscall SAVClass::SAVClass(SAVClass *this)

{
  HoverCraftClass::HoverCraftClass((HoverCraftClass *)this);
  this->_padding_ = 0;
  this[1]._padding_ = 0x43160000;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x53415600;
  this->_padding_ = (int)"sav";
  return this;
}
