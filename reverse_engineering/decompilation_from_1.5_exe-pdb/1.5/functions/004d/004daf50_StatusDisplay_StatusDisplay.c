/*
 * Entry: 004daf50
 * Name: StatusDisplay::StatusDisplay
 * Namespace: StatusDisplay
 * Signature: StatusDisplay * StatusDisplay(StatusDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

StatusDisplay * __thiscall StatusDisplay::StatusDisplay(StatusDisplay *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::AddView((DisplayInterface *)this,0,1);
  DisplayInterface::AddView((DisplayInterface *)this,2,1);
  DisplayInterface::AddView((DisplayInterface *)this,1,1);
  DisplayInterface::AddView((DisplayInterface *)this,7,1);
  return this;
}
