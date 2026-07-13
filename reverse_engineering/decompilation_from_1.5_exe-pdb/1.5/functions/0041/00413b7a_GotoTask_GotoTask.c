/*
 * Entry: 00413b7a
 * Name: GotoTask::GotoTask
 * Namespace: GotoTask
 * Signature: GotoTask * GotoTask(GotoTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GotoTask * __thiscall GotoTask::GotoTask(GotoTask *this)

{
  UnitTask::UnitTask((UnitTask *)this);
  (this->destPoint).x = 0.0;
  (this->destPoint).y = 0.0;
  this->_padding_ = 1;
  this->_padding_ = 1;
  (this->destPoint).z = 0.0;
  this->path = (AiPath *)0x0;
  this->release = false;
  this->pathPoint = 0;
  this->exact = false;
  this->skipdone = false;
  this->_padding_ = (int)&_vftable_;
  return this;
}
