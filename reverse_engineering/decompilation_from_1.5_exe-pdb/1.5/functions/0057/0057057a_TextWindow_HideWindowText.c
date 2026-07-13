/*
 * Entry: 0057057a
 * Name: TextWindow::HideWindowText
 * Namespace: TextWindow
 * Signature: int HideWindowText(TextWindow * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextWindow::HideWindowText(TextWindow *this,int param_1)

{
  int iVar1;
  
  if (this->nTextVisible == 0) {
    iVar1 = 0;
  }
  else {
    this->nTextVisible = 0;
    if (param_1 != 0) {
      (**(code **)(this->_padding_ + 4))(0);
    }
    iVar1 = 1;
  }
  return iVar1;
}
