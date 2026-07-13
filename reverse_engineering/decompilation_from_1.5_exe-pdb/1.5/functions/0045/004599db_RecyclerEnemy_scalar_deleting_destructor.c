/*
 * Entry: 004599db
 * Name: RecyclerEnemy::`scalar_deleting_destructor'
 * Namespace: RecyclerEnemy
 * Signature: void * `scalar_deleting_destructor'(RecyclerEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RecyclerEnemy::_scalar_deleting_destructor_(RecyclerEnemy *this,uint param_1)

{
  RecyclerProcess::~RecyclerProcess((RecyclerProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
