/*
 * Entry: 004d4749
 * Name: PathDisplay::~PathDisplay
 * Namespace: PathDisplay
 * Signature: void ~PathDisplay(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::~PathDisplay(PathDisplay *this)

{
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  return;
}
