/*
 * Entry: 00415250
 * Name: HuntTask::Load
 * Namespace: HuntTask
 * Signature: bool Load(HuntTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall HuntTask::Load(HuntTask *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = in_ptr(param_1,&this->my_craft,4,"my_craft",this);
  if ((bVar1) && (bVar1 = GotoTask::Load((GotoTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
