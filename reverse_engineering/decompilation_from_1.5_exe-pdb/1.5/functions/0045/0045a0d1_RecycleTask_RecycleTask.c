/*
 * Entry: 0045a0d1
 * Name: RecycleTask::RecycleTask
 * Namespace: RecycleTask
 * Signature: RecycleTask * RecycleTask(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RecycleTask * __thiscall RecycleTask::RecycleTask(RecycleTask *this)

{
  AiTask::AiTask((AiTask *)this);
  this->me = (Craft *)0x0;
  this->curState = 0;
  (this->lastScrap).x = 0.0;
  this->nextStuck = 0.0;
  (this->lastScrap).y = -1.0;
  (this->lastScrap).z = 0.0;
  (this->lastStuck).x = 0.0;
  (this->lastStuck).y = 0.0;
  (this->lastStuck).z = 0.0;
  this->nextCheck = 0.0;
  (this->where).x = 0.0;
  (this->where).y = 0.0;
  (this->where).z = 0.0;
  (this->lastRecyclerPos).x = 0.0;
  (this->lastRecyclerPos).y = 0.0;
  (this->lastRecyclerPos).z = 0.0;
  this->subtask = (AiTask *)0x0;
  this->scrapHandle = 0;
  this->dropHandle = 0;
  this->stuckState = 0;
  this->_padding_ = (int)&_vftable_;
  this->nextState = 1;
  return this;
}
