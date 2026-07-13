/*
 * Entry: 004ad21f
 * Name: RepairDepotClass::`scalar_deleting_destructor'
 * Namespace: RepairDepotClass
 * Signature: void * `scalar_deleting_destructor'(RepairDepotClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
RepairDepotClass::_scalar_deleting_destructor_(RepairDepotClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
