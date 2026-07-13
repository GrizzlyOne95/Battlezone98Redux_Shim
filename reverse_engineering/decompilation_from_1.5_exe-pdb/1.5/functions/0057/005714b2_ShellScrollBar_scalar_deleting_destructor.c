/*
 * Entry: 005714b2
 * Name: ShellScrollBar::`scalar_deleting_destructor'
 * Namespace: ShellScrollBar
 * Signature: void * `scalar_deleting_destructor'(ShellScrollBar * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ShellScrollBar::_scalar_deleting_destructor_(ShellScrollBar *this,uint param_1)

{
  ~ShellScrollBar(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
