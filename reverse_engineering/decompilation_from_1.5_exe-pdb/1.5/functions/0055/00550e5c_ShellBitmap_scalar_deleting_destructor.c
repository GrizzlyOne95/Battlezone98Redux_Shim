/*
 * Entry: 00550e5c
 * Name: ShellBitmap::`scalar_deleting_destructor'
 * Namespace: ShellBitmap
 * Signature: void * `scalar_deleting_destructor'(ShellBitmap * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ShellBitmap::_scalar_deleting_destructor_(ShellBitmap *this,uint param_1)

{
  ~ShellBitmap(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
