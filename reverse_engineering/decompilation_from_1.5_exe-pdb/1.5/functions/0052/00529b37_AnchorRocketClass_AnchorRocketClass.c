/*
 * Entry: 00529b37
 * Name: AnchorRocketClass::AnchorRocketClass
 * Namespace: AnchorRocketClass
 * Signature: AnchorRocketClass * AnchorRocketClass(AnchorRocketClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnchorRocketClass * __thiscall AnchorRocketClass::AnchorRocketClass(AnchorRocketClass *this)

{
  RocketClass::RocketClass((RocketClass *)this);
  this->anchorTime = 10.0;
  this->_padding_ = (int)&_vftable_;
  this->accelDrag = 10.0;
  this->_padding_ = 0x414e4348;
  this->_padding_ = (int)"anchor";
  this->alphaDrag = 5.0;
  return this;
}
