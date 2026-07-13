/*
 * Entry: 0053b416
 * Name: TargetingGun::`scalar_deleting_destructor'
 * Namespace: TargetingGun
 * Signature: void * `scalar_deleting_destructor'(TargetingGun * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TargetingGun::_scalar_deleting_destructor_(TargetingGun *this,uint param_1)

{
  ~TargetingGun(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
