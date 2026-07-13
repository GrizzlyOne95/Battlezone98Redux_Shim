/*
 * Entry: 004da9a4
 * Name: SniperInterface::SniperInterface
 * Namespace: SniperInterface
 * Signature: SniperInterface * SniperInterface(SniperInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SniperInterface * __thiscall SniperInterface::SniperInterface(SniperInterface *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::AddView((DisplayInterface *)this,0,-1);
  return this;
}
