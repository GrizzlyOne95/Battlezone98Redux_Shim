/*
 * Entry: 00456e85
 * Name: PatrolTask::Load
 * Namespace: PatrolTask
 * Signature: bool Load(PatrolTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PatrolTask::Load(PatrolTask *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,(int *)&this->patrol_type,4);
  if ((((bVar1) && (bVar1 = in_ptr(param_1,&this->my_craft,4,"my_craft",this), bVar1)) &&
      (bVar1 = ::in(param_1,(int *)&this->patrol_dir,4), bVar1)) &&
     (bVar1 = GotoTask::Load((GotoTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
