/*
 * Entry: 0049f9ad
 * Name: HowitzerClass::`scalar_deleting_destructor'
 * Namespace: HowitzerClass
 * Signature: void * `scalar_deleting_destructor'(HowitzerClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall HowitzerClass::_scalar_deleting_destructor_(HowitzerClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  TurretTankClass::~TurretTankClass((TurretTankClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
