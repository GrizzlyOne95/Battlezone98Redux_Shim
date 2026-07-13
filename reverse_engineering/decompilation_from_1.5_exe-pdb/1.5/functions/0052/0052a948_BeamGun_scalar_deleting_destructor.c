/*
 * Entry: 0052a948
 * Name: BeamGun::`scalar_deleting_destructor'
 * Namespace: BeamGun
 * Signature: void * `scalar_deleting_destructor'(BeamGun * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BeamGun::_scalar_deleting_destructor_(BeamGun *this,uint param_1)

{
  ~BeamGun(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
