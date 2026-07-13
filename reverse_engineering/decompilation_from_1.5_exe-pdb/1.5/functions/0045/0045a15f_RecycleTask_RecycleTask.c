/*
 * Entry: 0045a15f
 * Name: RecycleTask::RecycleTask
 * Namespace: RecycleTask
 * Signature: RecycleTask * RecycleTask(RecycleTask * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RecycleTask * __thiscall
RecycleTask::RecycleTask(RecycleTask *this,Craft *param_1,GameObject *param_2)

{
  int iVar1;
  
  AiTask::AiTask((AiTask *)this);
  this->me = param_1;
  iVar1 = 0;
  (this->lastScrap).x = 0.0;
  (this->lastScrap).y = -1.0;
  this->_padding_ = (int)&_vftable_;
  this->curState = 0;
  this->nextState = (param_2 != (GameObject *)0x0) + 1;
  this->subtask = (AiTask *)0x0;
  (this->lastScrap).z = 0.0;
  if (param_2 != (GameObject *)0x0) {
    iVar1 = GameObject::GetHandle(param_2);
  }
  this->nextStuck = 0.0;
  this->dropHandle = 0;
  (this->lastStuck).x = 0.0;
  (this->lastStuck).y = 0.0;
  (this->lastStuck).z = 0.0;
  this->stuckState = 0;
  this->nextCheck = 0.0;
  (this->where).x = 0.0;
  (this->where).y = 0.0;
  (this->where).z = 0.0;
  (this->lastRecyclerPos).x = 0.0;
  (this->lastRecyclerPos).y = 0.0;
  this->scrapHandle = iVar1;
  (this->lastRecyclerPos).z = 0.0;
  PostInit(this);
  return this;
}
