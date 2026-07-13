/*
 * Entry: 004daf8e
 * Name: StatusDisplay::~StatusDisplay
 * Namespace: StatusDisplay
 * Signature: void ~StatusDisplay(StatusDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall StatusDisplay::~StatusDisplay(StatusDisplay *this)

{
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  return;
}
