/*
 * Entry: 0047bffb
 * Name: AnimBuildingClass::`scalar_deleting_destructor'
 * Namespace: AnimBuildingClass
 * Signature: void * `scalar_deleting_destructor'(AnimBuildingClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
AnimBuildingClass::_scalar_deleting_destructor_(AnimBuildingClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
