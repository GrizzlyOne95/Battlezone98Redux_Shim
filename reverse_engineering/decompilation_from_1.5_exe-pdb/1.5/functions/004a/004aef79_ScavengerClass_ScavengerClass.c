/*
 * Entry: 004aef79
 * Name: ScavengerClass::ScavengerClass
 * Namespace: ScavengerClass
 * Signature: ScavengerClass * ScavengerClass(ScavengerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScavengerClass * __thiscall ScavengerClass::ScavengerClass(ScavengerClass *this)

{
  HoverCraftClass::HoverCraftClass((HoverCraftClass *)this);
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x53434156;
  this->_padding_ = (int)"scavenger";
  this->_padding_ = 0x19;
  this->_padding_ = 0x22;
  this->soundPickup[4] = '\x03';
  this->soundPickup[5] = '\0';
  this->soundPickup[6] = '\0';
  this->soundPickup[7] = '\0';
  strncpy(this->soundPickup + 8,"suck.wav",0x10);
  this->deployMsg[8] = '\0';
  this->foundMsg[8] = '\0';
  this->notFoundMsg[8] = '\0';
  this->noDropMsg[8] = '\0';
  return this;
}
