/*
 * Entry: 004b1499
 * Name: SpawnBuoyClass::`scalar_deleting_destructor'
 * Namespace: SpawnBuoyClass
 * Signature: void * `scalar_deleting_destructor'(SpawnBuoyClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SpawnBuoyClass::_scalar_deleting_destructor_(SpawnBuoyClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
