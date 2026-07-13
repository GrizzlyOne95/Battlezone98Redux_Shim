/*
 * Entry: 00535131
 * Name: OrdnanceClass::`scalar_deleting_destructor'
 * Namespace: OrdnanceClass
 * Signature: void * `scalar_deleting_destructor'(OrdnanceClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall OrdnanceClass::_scalar_deleting_destructor_(OrdnanceClass *this,uint param_1)

{
  ~OrdnanceClass(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
