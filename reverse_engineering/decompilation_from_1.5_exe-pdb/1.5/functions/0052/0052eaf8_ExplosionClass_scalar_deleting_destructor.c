/*
 * Entry: 0052eaf8
 * Name: ExplosionClass::`scalar_deleting_destructor'
 * Namespace: ExplosionClass
 * Signature: void * `scalar_deleting_destructor'(ExplosionClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ExplosionClass::_scalar_deleting_destructor_(ExplosionClass *this,uint param_1)

{
  ~ExplosionClass(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
