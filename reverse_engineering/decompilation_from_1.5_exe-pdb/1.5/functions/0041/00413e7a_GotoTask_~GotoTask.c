/*
 * Entry: 00413e7a
 * Name: GotoTask::~GotoTask
 * Namespace: GotoTask
 * Signature: void ~GotoTask(GotoTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GotoTask::~GotoTask(GotoTask *this)

{
  this->_padding_ = (int)&_vftable_;
  CleanState(this);
  this->_padding_ = 0xd;
  if ((this->release != false) && (this->path != (AiPath *)0x0)) {
    AiPath::Release(this->path);
  }
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
