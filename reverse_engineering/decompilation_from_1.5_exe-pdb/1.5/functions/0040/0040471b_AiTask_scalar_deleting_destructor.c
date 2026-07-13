/*
 * Entry: 0040471b
 * Name: AiTask::`scalar_deleting_destructor'
 * Namespace: AiTask
 * Signature: void * `scalar_deleting_destructor'(AiTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall AiTask::_scalar_deleting_destructor_(AiTask *this,uint param_1)

{
  ~AiTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
