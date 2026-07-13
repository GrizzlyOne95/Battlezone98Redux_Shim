/*
 * Entry: 00459af9
 * Name: RecycleTask::Load
 * Namespace: RecycleTask
 * Signature: bool Load(RecycleTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RecycleTask::Load(RecycleTask *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = in_ptr(param_1,&this->me,4,"me",this);
  if (((((bVar1) && (bVar1 = in_ptr(param_1,&this->subtask,4,"subtask",this), bVar1)) &&
       (bVar1 = ::in(param_1,&this->lastScrap,0xc), bVar1)) &&
      ((((bVar1 = ::in(param_1,&this->scrapHandle,4), bVar1 &&
         (bVar1 = ::in(param_1,&this->dropHandle,4), bVar1)) &&
        ((bVar1 = ::in(param_1,&this->curState,4), bVar1 &&
         ((bVar1 = ::in(param_1,&this->nextState,4), bVar1 &&
          (bVar1 = ::in(param_1,&this->where,0xc), bVar1)))))) &&
       (bVar1 = ::in(param_1,&this->nextCheck,4), bVar1)))) &&
     ((((bVar1 = ::in(param_1,&this->lastRecyclerPos,0xc), bVar1 &&
        (bVar1 = ::in(param_1,&this->nextStuck,4), bVar1)) &&
       (bVar1 = ::in(param_1,&this->lastStuck,0xc), bVar1)) &&
      ((bVar1 = ::in(param_1,&this->stuckState,4), bVar1 &&
       (bVar1 = AiTask::Load((AiTask *)this,param_1), bVar1)))))) {
    return true;
  }
  return false;
}
