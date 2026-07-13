/*
 * Entry: 0049fbf5
 * Name: MinelayerClass::MinelayerClass
 * Namespace: MinelayerClass
 * Signature: MinelayerClass * MinelayerClass(MinelayerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MinelayerClass * __thiscall MinelayerClass::MinelayerClass(MinelayerClass *this)

{
  HoverCraftClass::HoverCraftClass((HoverCraftClass *)this);
  this->mineDist = 100.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x4d4c5952;
  *(undefined4 *)&this->field_0x3c4 = 0x41a00000;
  this->_padding_ = (int)"minelayer";
  this->_padding_ = 0xf;
  this[1]._padding_ = 0x42340000;
  this->_padding_ = 0x18;
  return this;
}
