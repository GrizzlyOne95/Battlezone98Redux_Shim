/*
 * Entry: 0047f918
 * Name: Attachable::`scalar_deleting_destructor'
 * Namespace: Attachable
 * Signature: void * `scalar_deleting_destructor'(Attachable * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Attachable::_scalar_deleting_destructor_(Attachable *this,uint param_1)

{
  ~Attachable(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
