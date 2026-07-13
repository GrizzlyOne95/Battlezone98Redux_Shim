/*
 * Entry: 00457d2f
 * Name: PersonEnemy::`scalar_deleting_destructor'
 * Namespace: PersonEnemy
 * Signature: void * `scalar_deleting_destructor'(PersonEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PersonEnemy::_scalar_deleting_destructor_(PersonEnemy *this,uint param_1)

{
  PersonProcess::~PersonProcess((PersonProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
