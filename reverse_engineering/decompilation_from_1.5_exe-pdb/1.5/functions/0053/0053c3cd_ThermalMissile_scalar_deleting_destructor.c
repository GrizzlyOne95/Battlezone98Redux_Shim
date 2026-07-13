/*
 * Entry: 0053c3cd
 * Name: ThermalMissile::`scalar_deleting_destructor'
 * Namespace: ThermalMissile
 * Signature: void * `scalar_deleting_destructor'(ThermalMissile * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ThermalMissile::_scalar_deleting_destructor_(ThermalMissile *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Missile::~Missile((Missile *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
