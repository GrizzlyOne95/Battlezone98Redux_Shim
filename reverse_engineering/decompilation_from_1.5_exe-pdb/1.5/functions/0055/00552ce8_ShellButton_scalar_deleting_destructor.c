/*
 * Entry: 00552ce8
 * Name: ShellButton::`scalar_deleting_destructor'
 * Namespace: ShellButton
 * Signature: void * `scalar_deleting_destructor'(ShellButton * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ShellButton::_scalar_deleting_destructor_(ShellButton *this,uint param_1)

{
  ~ShellButton(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
