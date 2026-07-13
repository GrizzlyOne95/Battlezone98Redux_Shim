/*
 * Entry: 00530f2b
 * Name: LauncherClass::`scalar_deleting_destructor'
 * Namespace: LauncherClass
 * Signature: void * `scalar_deleting_destructor'(LauncherClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall LauncherClass::_scalar_deleting_destructor_(LauncherClass *this,uint param_1)

{
  ~LauncherClass(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
