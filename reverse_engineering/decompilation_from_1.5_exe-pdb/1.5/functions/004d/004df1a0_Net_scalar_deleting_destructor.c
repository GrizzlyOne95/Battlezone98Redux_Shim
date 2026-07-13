/*
 * Entry: 004df1a0
 * Name: Net::`scalar_deleting_destructor'
 * Namespace: Net
 * Signature: void * `scalar_deleting_destructor'(Net * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Net::_scalar_deleting_destructor_(Net *this,uint param_1)

{
  ~Net(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
