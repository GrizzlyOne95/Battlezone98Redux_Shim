/*
 * Entry: 00470859
 * Name: BomberEnemy::`scalar_deleting_destructor'
 * Namespace: BomberEnemy
 * Signature: void * `scalar_deleting_destructor'(BomberEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BomberEnemy::_scalar_deleting_destructor_(BomberEnemy *this,uint param_1)

{
  WingmanProcess::~WingmanProcess((WingmanProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
