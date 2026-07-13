/*
 * Entry: 00401797
 * Name: stdext::bad_alloc::`scalar_deleting_destructor'
 * Namespace: stdext::bad_alloc
 * Signature: void * `scalar_deleting_destructor'(bad_alloc * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall stdext::bad_alloc::_scalar_deleting_destructor_(bad_alloc *this,uint param_1)

{
  *(undefined ***)this = &exception::_vftable_;
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
