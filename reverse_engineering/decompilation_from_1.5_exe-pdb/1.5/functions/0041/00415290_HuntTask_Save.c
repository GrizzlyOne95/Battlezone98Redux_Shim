/*
 * Entry: 00415290
 * Name: HuntTask::Save
 * Namespace: HuntTask
 * Signature: bool Save(HuntTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall HuntTask::Save(HuntTask *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = out_ptr(param_1,&this->my_craft,4,"my_craft");
  if ((bVar1) && (bVar1 = GotoTask::Save((GotoTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
