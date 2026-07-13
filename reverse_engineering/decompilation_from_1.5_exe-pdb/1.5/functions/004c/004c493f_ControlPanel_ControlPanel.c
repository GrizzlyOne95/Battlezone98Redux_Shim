/*
 * Entry: 004c493f
 * Name: ControlPanel::ControlPanel
 * Namespace: ControlPanel
 * Signature: ControlPanel * ControlPanel(ControlPanel * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ControlPanel * __thiscall ControlPanel::ControlPanel(ControlPanel *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  ModeList::RemoveAllModes(&this->currentModes);
  (this->currentModes).activeSlot = -1;
  DisplayInterface::AddView((DisplayInterface *)this,0,1);
  DisplayInterface::AddView((DisplayInterface *)this,2,1);
  DisplayInterface::AddView((DisplayInterface *)this,1,1);
  DisplayInterface::AddView((DisplayInterface *)this,7,1);
  DisplayInterface::AddView((DisplayInterface *)this,3,1);
  return this;
}
