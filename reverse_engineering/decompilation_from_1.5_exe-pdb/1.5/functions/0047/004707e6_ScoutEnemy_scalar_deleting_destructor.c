/*
 * Entry: 004707e6
 * Name: ScoutEnemy::`scalar_deleting_destructor'
 * Namespace: ScoutEnemy
 * Signature: void * `scalar_deleting_destructor'(ScoutEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScoutEnemy::_scalar_deleting_destructor_(ScoutEnemy *this,uint param_1)

{
  WingmanProcess::~WingmanProcess((WingmanProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
