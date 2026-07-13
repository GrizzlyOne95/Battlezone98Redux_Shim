/*
 * Entry: 0041595e
 * Name: Inst01Event::`scalar_deleting_destructor'
 * Namespace: Inst01Event
 * Signature: void * `scalar_deleting_destructor'(Inst01Event * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Inst01Event::_scalar_deleting_destructor_(Inst01Event *this,uint param_1)

{
  AiProcess::~AiProcess((AiProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
