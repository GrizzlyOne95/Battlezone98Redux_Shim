/*
 * Entry: 00508da2
 * Name: Scheduler::`scalar_deleting_destructor'
 * Namespace: Scheduler
 * Signature: void * `scalar_deleting_destructor'(Scheduler * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Scheduler::_scalar_deleting_destructor_(Scheduler *this,uint param_1)

{
  ~Scheduler(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
