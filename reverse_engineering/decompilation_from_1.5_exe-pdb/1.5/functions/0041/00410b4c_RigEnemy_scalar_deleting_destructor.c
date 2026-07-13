/*
 * Entry: 00410b4c
 * Name: RigEnemy::`scalar_deleting_destructor'
 * Namespace: RigEnemy
 * Signature: void * `scalar_deleting_destructor'(RigEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RigEnemy::_scalar_deleting_destructor_(RigEnemy *this,uint param_1)

{
  RigProcess::~RigProcess((RigProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
