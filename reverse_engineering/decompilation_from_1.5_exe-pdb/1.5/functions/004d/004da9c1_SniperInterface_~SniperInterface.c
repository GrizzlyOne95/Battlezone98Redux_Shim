/*
 * Entry: 004da9c1
 * Name: SniperInterface::~SniperInterface
 * Namespace: SniperInterface
 * Signature: void ~SniperInterface(SniperInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SniperInterface::~SniperInterface(SniperInterface *this)

{
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  return;
}
