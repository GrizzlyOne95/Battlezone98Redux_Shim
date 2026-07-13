/*
 * Entry: 0040d28f
 * Name: SLFEnemy::`scalar_deleting_destructor'
 * Namespace: SLFEnemy
 * Signature: void * `scalar_deleting_destructor'(SLFEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SLFEnemy::_scalar_deleting_destructor_(SLFEnemy *this,uint param_1)

{
  ArmoryProcess::~ArmoryProcess((ArmoryProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
