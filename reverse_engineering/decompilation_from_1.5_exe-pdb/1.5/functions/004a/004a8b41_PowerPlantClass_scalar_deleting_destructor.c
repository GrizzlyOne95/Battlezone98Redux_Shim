/*
 * Entry: 004a8b41
 * Name: PowerPlantClass::`scalar_deleting_destructor'
 * Namespace: PowerPlantClass
 * Signature: void * `scalar_deleting_destructor'(PowerPlantClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PowerPlantClass::_scalar_deleting_destructor_(PowerPlantClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
