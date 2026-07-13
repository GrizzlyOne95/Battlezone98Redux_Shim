/*
 * Entry: 004639e1
 * Name: TorpedoProcess::`scalar_deleting_destructor'
 * Namespace: TorpedoProcess
 * Signature: void * `scalar_deleting_destructor'(TorpedoProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TorpedoProcess::_scalar_deleting_destructor_(TorpedoProcess *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  AiProcess::~AiProcess((AiProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
