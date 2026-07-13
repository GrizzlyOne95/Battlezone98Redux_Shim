/*
 * Entry: 00483582
 * Name: BuildingClass::`scalar_deleting_destructor'
 * Namespace: BuildingClass
 * Signature: void * `scalar_deleting_destructor'(BuildingClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BuildingClass::_scalar_deleting_destructor_(BuildingClass *this,uint param_1)

{
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
