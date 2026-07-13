/*
 * Entry: 005704db
 * Name: TextWindow::SetWindowTextColor
 * Namespace: TextWindow
 * Signature: int SetWindowTextColor(TextWindow * this, ulong param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextWindow::SetWindowTextColor(TextWindow *this,ulong param_1,int param_2)

{
  this->textColor = param_1;
  if (param_2 != 0) {
    (**(code **)(this->_padding_ + 4))(0);
  }
  return 1;
}
