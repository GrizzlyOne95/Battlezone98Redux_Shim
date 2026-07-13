/*
 * Entry: 005704c1
 * Name: TextWindow::CheckRollOver
 * Namespace: TextWindow
 * Signature: int CheckRollOver(TextWindow * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextWindow::CheckRollOver(TextWindow *this,int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = check_roll_over(&this->twRect,param_1,param_2);
  return iVar1;
}
