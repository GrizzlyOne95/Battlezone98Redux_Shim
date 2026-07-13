/*
 * Entry: 00412fb3
 * Name: GechEnemy::`scalar_deleting_destructor'
 * Namespace: GechEnemy
 * Signature: void * `scalar_deleting_destructor'(GechEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GechEnemy::_scalar_deleting_destructor_(GechEnemy *this,uint param_1)

{
  GechProcess::~GechProcess((GechProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
