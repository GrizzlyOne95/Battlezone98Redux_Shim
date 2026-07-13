/*
 * Entry: 00570126
 * Name: ShellScrollBar::CheckRollOver
 * Namespace: ShellScrollBar
 * Signature: int CheckRollOver(ShellScrollBar * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellScrollBar::CheckRollOver(ShellScrollBar *this,int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = check_roll_over(&this->scRect,param_1,param_2);
  return iVar1;
}
