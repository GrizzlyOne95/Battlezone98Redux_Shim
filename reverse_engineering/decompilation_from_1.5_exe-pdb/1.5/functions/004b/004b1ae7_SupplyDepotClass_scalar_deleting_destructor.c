/*
 * Entry: 004b1ae7
 * Name: SupplyDepotClass::`scalar_deleting_destructor'
 * Namespace: SupplyDepotClass
 * Signature: void * `scalar_deleting_destructor'(SupplyDepotClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
SupplyDepotClass::_scalar_deleting_destructor_(SupplyDepotClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
