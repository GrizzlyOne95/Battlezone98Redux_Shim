/*
 * Entry: 004cef6d
 * Name: InfoDisplay::InfoDisplay
 * Namespace: InfoDisplay
 * Signature: InfoDisplay * InfoDisplay(InfoDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

InfoDisplay * __thiscall InfoDisplay::InfoDisplay(InfoDisplay *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->objectiveLast = 0.0;
  this->_padding_ = (int)&_vftable_;
  this->objectiveCount = 0;
  this->objectShow = false;
  this->objectSave = (GameObject *)0x0;
  DisplayInterface::AddView((DisplayInterface *)this,0,0);
  DisplayInterface::AddView((DisplayInterface *)this,2,0);
  DisplayInterface::AddView((DisplayInterface *)this,1,0);
  DisplayInterface::AddView((DisplayInterface *)this,7,0);
  return this;
}
