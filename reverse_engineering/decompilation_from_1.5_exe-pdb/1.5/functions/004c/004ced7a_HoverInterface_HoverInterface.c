/*
 * Entry: 004ced7a
 * Name: HoverInterface::HoverInterface
 * Namespace: HoverInterface
 * Signature: HoverInterface * HoverInterface(HoverInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HoverInterface * __thiscall HoverInterface::HoverInterface(HoverInterface *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::AddView((DisplayInterface *)this,3,2);
  DisplayInterface::AddView((DisplayInterface *)this,0,2);
  DisplayInterface::AddView((DisplayInterface *)this,7,2);
  return this;
}
