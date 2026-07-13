/*
 * Entry: 00531540
 * Name: MachineGunClass::`scalar_deleting_destructor'
 * Namespace: MachineGunClass
 * Signature: void * `scalar_deleting_destructor'(MachineGunClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MachineGunClass::_scalar_deleting_destructor_(MachineGunClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  CannonClass::~CannonClass((CannonClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
