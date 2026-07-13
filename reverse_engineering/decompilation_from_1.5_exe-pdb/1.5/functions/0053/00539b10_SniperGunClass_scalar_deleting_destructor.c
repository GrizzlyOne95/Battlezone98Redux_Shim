/*
 * Entry: 00539b10
 * Name: SniperGunClass::`scalar_deleting_destructor'
 * Namespace: SniperGunClass
 * Signature: void * `scalar_deleting_destructor'(SniperGunClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SniperGunClass::_scalar_deleting_destructor_(SniperGunClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  CannonClass::~CannonClass((CannonClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
