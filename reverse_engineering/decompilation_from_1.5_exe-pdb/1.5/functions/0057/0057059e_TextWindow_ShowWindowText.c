/*
 * Entry: 0057059e
 * Name: TextWindow::ShowWindowText
 * Namespace: TextWindow
 * Signature: int ShowWindowText(TextWindow * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextWindow::ShowWindowText(TextWindow *this,int param_1)

{
  int iVar1;
  
  if (this->nTextVisible == 0) {
    this->nTextVisible = 1;
    if (param_1 != 0) {
      (**(code **)(this->_padding_ + 4))(0);
    }
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}
