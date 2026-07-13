/*
 * Entry: 00529c11
 * Name: AnchorRocketClass::~AnchorRocketClass
 * Namespace: AnchorRocketClass
 * Signature: void ~AnchorRocketClass(AnchorRocketClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnchorRocketClass::~AnchorRocketClass(AnchorRocketClass *this)

{
  this->_padding_ = (int)&_vftable_;
  RocketClass::~RocketClass((RocketClass *)this);
  return;
}
