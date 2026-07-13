/*
 * Entry: 0041193f
 * Name: MUFEnemy::`scalar_deleting_destructor'
 * Namespace: MUFEnemy
 * Signature: void * `scalar_deleting_destructor'(MUFEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MUFEnemy::_scalar_deleting_destructor_(MUFEnemy *this,uint param_1)

{
  RecyclerProcess::~RecyclerProcess((RecyclerProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
