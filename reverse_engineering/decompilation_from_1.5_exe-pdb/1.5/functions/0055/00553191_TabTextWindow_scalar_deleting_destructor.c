/*
 * Entry: 00553191
 * Name: TabTextWindow::`scalar_deleting_destructor'
 * Namespace: TabTextWindow
 * Signature: void * `scalar_deleting_destructor'(TabTextWindow * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TabTextWindow::_scalar_deleting_destructor_(TabTextWindow *this,uint param_1)

{
  ~TabTextWindow(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
