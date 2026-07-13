/*
 * Entry: 0056f3dc
 * Name: ShellButton::CheckRollOver
 * Namespace: ShellButton
 * Signature: int CheckRollOver(ShellButton * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellButton::CheckRollOver(ShellButton *this,int param_1,int param_2)

{
  int iVar1;
  
  if ((this->nButtonVisible == 0) || (this->nButtonEnable == 0)) {
    iVar1 = 0;
  }
  else {
    iVar1 = check_roll_over(&this->buttonRect,param_1,param_2);
  }
  return iVar1;
}
