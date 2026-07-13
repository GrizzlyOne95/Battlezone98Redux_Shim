/*
 * Entry: 0056f409
 * Name: ShellButton::MoveButton
 * Namespace: ShellButton
 * Signature: int MoveButton(ShellButton * this, int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellButton::MoveButton(ShellButton *this,int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = (this->buttonRect).top;
  (this->buttonRect).right = ((this->buttonRect).right - (this->buttonRect).left) + param_1;
  (this->buttonRect).top = param_2;
  (this->buttonRect).left = param_1;
  (this->buttonRect).bottom = ((this->buttonRect).bottom - iVar1) + param_2;
  return 1;
}
