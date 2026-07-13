/*
 * Entry: 00552e74
 * Name: TextWindow::`scalar_deleting_destructor'
 * Namespace: TextWindow
 * Signature: void * `scalar_deleting_destructor'(TextWindow * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TextWindow::_scalar_deleting_destructor_(TextWindow *this,uint param_1)

{
  ~TextWindow(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
