/*
 * Entry: 00456e7a
 * Name: PatrolTask::~PatrolTask
 * Namespace: PatrolTask
 * Signature: void ~PatrolTask(PatrolTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PatrolTask::~PatrolTask(PatrolTask *this)

{
  this->_padding_ = (int)&_vftable_;
  GotoTask::~GotoTask((GotoTask *)this);
  return;
}
