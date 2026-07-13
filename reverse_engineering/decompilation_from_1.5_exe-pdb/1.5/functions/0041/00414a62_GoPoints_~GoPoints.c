/*
 * Entry: 00414a62
 * Name: GoPoints::~GoPoints
 * Namespace: GoPoints
 * Signature: void ~GoPoints(GoPoints * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GoPoints::~GoPoints(GoPoints *this)

{
  this->_padding_ = (int)&GotoTask::_vftable_;
  GotoTask::CleanState((GotoTask *)this);
  this->_padding_ = 0xd;
  if (((char)this->_padding_ != '\0') && ((AiPath *)this->_padding_ != (AiPath *)0x0)) {
    AiPath::Release((AiPath *)this->_padding_);
  }
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
