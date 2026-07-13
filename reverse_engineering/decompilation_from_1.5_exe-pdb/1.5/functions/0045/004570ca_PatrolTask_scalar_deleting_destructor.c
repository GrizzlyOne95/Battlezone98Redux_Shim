/*
 * Entry: 004570ca
 * Name: PatrolTask::`scalar_deleting_destructor'
 * Namespace: PatrolTask
 * Signature: void * `scalar_deleting_destructor'(PatrolTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PatrolTask::_scalar_deleting_destructor_(PatrolTask *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
