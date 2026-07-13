/*
 * Entry: 0040bfba
 * Name: APCEnemy::`scalar_deleting_destructor'
 * Namespace: APCEnemy
 * Signature: void * `scalar_deleting_destructor'(APCEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall APCEnemy::_scalar_deleting_destructor_(APCEnemy *this,uint param_1)

{
  APCProcess::~APCProcess((APCProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
