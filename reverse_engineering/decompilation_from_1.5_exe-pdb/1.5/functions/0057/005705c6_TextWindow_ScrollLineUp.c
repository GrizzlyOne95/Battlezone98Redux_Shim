/*
 * Entry: 005705c6
 * Name: TextWindow::ScrollLineUp
 * Namespace: TextWindow
 * Signature: int ScrollLineUp(TextWindow * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextWindow::ScrollLineUp(TextWindow *this,int param_1)

{
  if (param_1 == 0) {
    param_1 = -this->nFontHeight;
  }
  (**(code **)(this->_padding_ + 4))(param_1);
  return 1;
}
