/*
 * Entry: 004585cd
 * Name: PowerUpProcess::`scalar_deleting_destructor'
 * Namespace: PowerUpProcess
 * Signature: void * `scalar_deleting_destructor'(PowerUpProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PowerUpProcess::_scalar_deleting_destructor_(PowerUpProcess *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  AiProcess::~AiProcess((AiProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
