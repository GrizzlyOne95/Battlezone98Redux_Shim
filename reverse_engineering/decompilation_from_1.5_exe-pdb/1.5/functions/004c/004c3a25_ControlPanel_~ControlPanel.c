/*
 * Entry: 004c3a25
 * Name: ControlPanel::~ControlPanel
 * Namespace: ControlPanel
 * Signature: void ~ControlPanel(ControlPanel * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::~ControlPanel(ControlPanel *this)

{
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  return;
}
