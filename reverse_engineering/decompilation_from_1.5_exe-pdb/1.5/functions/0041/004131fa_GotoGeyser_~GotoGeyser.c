/*
 * Entry: 004131fa
 * Name: GotoGeyser::~GotoGeyser
 * Namespace: GotoGeyser
 * Signature: void ~GotoGeyser(GotoGeyser * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GotoGeyser::~GotoGeyser(GotoGeyser *this)

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
