/*
 * Entry: 004633c7
 * Name: SoldierEnemy::`scalar_deleting_destructor'
 * Namespace: SoldierEnemy
 * Signature: void * `scalar_deleting_destructor'(SoldierEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SoldierEnemy::_scalar_deleting_destructor_(SoldierEnemy *this,uint param_1)

{
  SoldierProcess::~SoldierProcess((SoldierProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
