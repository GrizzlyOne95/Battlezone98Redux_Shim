/*
 * Entry: 004b3a36
 * Name: TugClass::TugClass
 * Namespace: TugClass
 * Signature: TugClass * TugClass(TugClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TugClass * __thiscall TugClass::TugClass(TugClass *this)

{
  HoverCraftClass::HoverCraftClass((HoverCraftClass *)this);
  this[1]._padding_ = 0x40800000;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x54554700;
  this->_padding_ = (int)"tug";
  this->_padding_ = 0x19;
  this->_padding_ = 0x22;
  return this;
}
