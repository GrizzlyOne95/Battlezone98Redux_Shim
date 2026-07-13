/*
 * Entry: 00456ef1
 * Name: PatrolTask::Save
 * Namespace: PatrolTask
 * Signature: bool Save(PatrolTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PatrolTask::Save(PatrolTask *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,(int *)&this->patrol_type,4,"patrol_type");
  if ((((bVar1) && (bVar1 = out_ptr(param_1,&this->my_craft,4,"my_craft"), bVar1)) &&
      (bVar1 = ::out(param_1,(int *)&this->patrol_dir,4,"patrol_dir"), bVar1)) &&
     (bVar1 = GotoTask::Save((GotoTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
