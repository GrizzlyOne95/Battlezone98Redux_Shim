/*
 * Entry: 00415352
 * Name: HuntTask::`scalar_deleting_destructor'
 * Namespace: HuntTask
 * Signature: void * `scalar_deleting_destructor'(HuntTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall HuntTask::_scalar_deleting_destructor_(HuntTask *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
