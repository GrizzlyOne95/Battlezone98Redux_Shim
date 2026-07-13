/*
 * Entry: 0052ccde
 * Name: ChargeGunClass::`scalar_deleting_destructor'
 * Namespace: ChargeGunClass
 * Signature: void * `scalar_deleting_destructor'(ChargeGunClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ChargeGunClass::_scalar_deleting_destructor_(ChargeGunClass *this,uint param_1)

{
  ~ChargeGunClass(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
