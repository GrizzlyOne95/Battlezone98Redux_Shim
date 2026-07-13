/*
 * Entry: 0051b5fc
 * Name: Goal::`scalar_deleting_destructor'
 * Namespace: Goal
 * Signature: void * `scalar_deleting_destructor'(Goal * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Goal::_scalar_deleting_destructor_(Goal *this,uint param_1)

{
  ~Goal(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
