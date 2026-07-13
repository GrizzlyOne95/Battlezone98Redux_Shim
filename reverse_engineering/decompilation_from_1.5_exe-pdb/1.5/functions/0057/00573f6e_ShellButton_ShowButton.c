/*
 * Entry: 00573f6e
 * Name: ShellButton::ShowButton
 * Namespace: ShellButton
 * Signature: int ShowButton(ShellButton * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellButton::ShowButton(ShellButton *this,int param_1)

{
  int iVar1;
  
  if (this->nButtonVisible == 0) {
    this->nButtonVisible = 1;
    if (param_1 != 0) {
      UpdateButton(this);
    }
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}
