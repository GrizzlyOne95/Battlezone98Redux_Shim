/*
 * Entry: 004b4a6d
 * Name: TurretCraftClass::`scalar_deleting_destructor'
 * Namespace: TurretCraftClass
 * Signature: void * `scalar_deleting_destructor'(TurretCraftClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
TurretCraftClass::_scalar_deleting_destructor_(TurretCraftClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  CraftClass::~CraftClass((CraftClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
