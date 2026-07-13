/*
 * Entry: 004c156b
 * Name: SelectionDisplay::SelectionDisplay
 * Namespace: SelectionDisplay
 * Signature: SelectionDisplay * SelectionDisplay(SelectionDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SelectionDisplay * __thiscall SelectionDisplay::SelectionDisplay(SelectionDisplay *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::AddView((DisplayInterface *)this,0,-1);
  DisplayInterface::AddView((DisplayInterface *)this,2,-1);
  DisplayInterface::AddView((DisplayInterface *)this,1,-1);
  DisplayInterface::AddView((DisplayInterface *)this,7,-1);
  DisplayInterface::AddView((DisplayInterface *)this,3,-1);
  return this;
}
