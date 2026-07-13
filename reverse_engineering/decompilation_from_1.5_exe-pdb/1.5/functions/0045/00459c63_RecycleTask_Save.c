/*
 * Entry: 00459c63
 * Name: RecycleTask::Save
 * Namespace: RecycleTask
 * Signature: bool Save(RecycleTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RecycleTask::Save(RecycleTask *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = out_ptr(param_1,&this->me,4,"me");
  if (((((bVar1) && (bVar1 = out_ptr(param_1,&this->subtask,4,"subtask"), bVar1)) &&
       (bVar1 = ::out(param_1,&this->lastScrap,0xc,"lastScrap"), bVar1)) &&
      ((((bVar1 = ::out(param_1,&this->scrapHandle,4,"scrapHandle"), bVar1 &&
         (bVar1 = ::out(param_1,&this->dropHandle,4,"dropHandle"), bVar1)) &&
        ((bVar1 = ::out(param_1,&this->curState,4,"curState"), bVar1 &&
         ((bVar1 = ::out(param_1,&this->nextState,4,"nextState"), bVar1 &&
          (bVar1 = ::out(param_1,&this->where,0xc,"where"), bVar1)))))) &&
       (bVar1 = ::out(param_1,&this->nextCheck,4,"nextCheck"), bVar1)))) &&
     ((((bVar1 = ::out(param_1,&this->lastRecyclerPos,0xc,"lastRecyclerPos"), bVar1 &&
        (bVar1 = ::out(param_1,&this->nextStuck,4,"nextStuck"), bVar1)) &&
       (bVar1 = ::out(param_1,&this->lastStuck,0xc,"lastStuck"), bVar1)) &&
      ((bVar1 = ::out(param_1,&this->stuckState,4,"stuckState"), bVar1 &&
       (bVar1 = AiTask::Save((AiTask *)this,param_1), bVar1)))))) {
    return true;
  }
  return false;
}
