/*
 * Entry: 0053c37a
 * Name: ThermalMissileClass::`scalar_deleting_destructor'
 * Namespace: ThermalMissileClass
 * Signature: void * `scalar_deleting_destructor'(ThermalMissileClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
ThermalMissileClass::_scalar_deleting_destructor_(ThermalMissileClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  MissileClass::~MissileClass((MissileClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
