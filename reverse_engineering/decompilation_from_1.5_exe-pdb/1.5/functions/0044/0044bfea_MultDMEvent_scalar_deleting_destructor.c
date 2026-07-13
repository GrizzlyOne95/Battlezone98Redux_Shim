/*
 * Entry: 0044bfea
 * Name: MultDMEvent::`scalar_deleting_destructor'
 * Namespace: MultDMEvent
 * Signature: void * `scalar_deleting_destructor'(MultDMEvent * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MultDMEvent::_scalar_deleting_destructor_(MultDMEvent *this,uint param_1)

{
  AiProcess::~AiProcess((AiProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
