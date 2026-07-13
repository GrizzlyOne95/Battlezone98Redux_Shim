/*
 * Entry: 00466fb3
 * Name: TugEnemy::`scalar_deleting_destructor'
 * Namespace: TugEnemy
 * Signature: void * `scalar_deleting_destructor'(TugEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TugEnemy::_scalar_deleting_destructor_(TugEnemy *this,uint param_1)

{
  TugProcess::~TugProcess((TugProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
