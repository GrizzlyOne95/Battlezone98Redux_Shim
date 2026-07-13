/*
 * Entry: 0045bd0d
 * Name: SAVEnemy::`scalar_deleting_destructor'
 * Namespace: SAVEnemy
 * Signature: void * `scalar_deleting_destructor'(SAVEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SAVEnemy::_scalar_deleting_destructor_(SAVEnemy *this,uint param_1)

{
  SAVProcess::~SAVProcess((SAVProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
