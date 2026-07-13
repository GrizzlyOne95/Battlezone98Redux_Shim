/*
 * Entry: 0045afb9
 * Name: RecycleTask::~RecycleTask
 * Namespace: RecycleTask
 * Signature: void ~RecycleTask(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::~RecycleTask(RecycleTask *this)

{
  this->_padding_ = (int)&_vftable_;
  CleanState(this);
  AiTask::~AiTask((AiTask *)this);
  return;
}
