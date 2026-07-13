/*
 * Entry: 004b6b3e
 * Name: TurretTankClass::`scalar_deleting_destructor'
 * Namespace: TurretTankClass
 * Signature: void * `scalar_deleting_destructor'(TurretTankClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TurretTankClass::_scalar_deleting_destructor_(TurretTankClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
