/*
 * Entry: 005705e7
 * Name: TextWindow::ScrollLineDown
 * Namespace: TextWindow
 * Signature: int ScrollLineDown(TextWindow * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextWindow::ScrollLineDown(TextWindow *this,int param_1)

{
  if (param_1 == 0) {
    param_1 = this->nFontHeight;
  }
  (**(code **)(this->_padding_ + 4))(param_1);
  return 1;
}
