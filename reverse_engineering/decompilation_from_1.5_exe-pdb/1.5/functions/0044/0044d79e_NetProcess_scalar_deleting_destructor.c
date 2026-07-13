/*
 * Entry: 0044d79e
 * Name: NetProcess::`scalar_deleting_destructor'
 * Namespace: NetProcess
 * Signature: void * `scalar_deleting_destructor'(NetProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall NetProcess::_scalar_deleting_destructor_(NetProcess *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  AiProcess::~AiProcess((AiProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
