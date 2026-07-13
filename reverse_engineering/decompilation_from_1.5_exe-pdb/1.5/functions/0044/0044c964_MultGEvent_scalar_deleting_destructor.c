/*
 * Entry: 0044c964
 * Name: MultGEvent::`scalar_deleting_destructor'
 * Namespace: MultGEvent
 * Signature: void * `scalar_deleting_destructor'(MultGEvent * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MultGEvent::_scalar_deleting_destructor_(MultGEvent *this,uint param_1)

{
  AiProcess::~AiProcess((AiProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
