/*
 * Entry: 0052ac97
 * Name: BeamGunClass::`scalar_deleting_destructor'
 * Namespace: BeamGunClass
 * Signature: void * `scalar_deleting_destructor'(BeamGunClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BeamGunClass::_scalar_deleting_destructor_(BeamGunClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  CannonClass::~CannonClass((CannonClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
