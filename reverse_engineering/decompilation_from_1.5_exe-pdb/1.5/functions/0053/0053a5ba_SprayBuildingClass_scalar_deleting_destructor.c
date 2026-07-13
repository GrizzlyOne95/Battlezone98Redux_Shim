/*
 * Entry: 0053a5ba
 * Name: SprayBuildingClass::`scalar_deleting_destructor'
 * Namespace: SprayBuildingClass
 * Signature: void * `scalar_deleting_destructor'(SprayBuildingClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
SprayBuildingClass::_scalar_deleting_destructor_(SprayBuildingClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
