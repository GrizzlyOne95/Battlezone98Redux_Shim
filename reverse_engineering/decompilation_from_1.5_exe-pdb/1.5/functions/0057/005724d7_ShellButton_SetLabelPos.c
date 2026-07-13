/*
 * Entry: 005724d7
 * Name: ShellButton::SetLabelPos
 * Namespace: ShellButton
 * Signature: int SetLabelPos(ShellButton * this, int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall
ShellButton::SetLabelPos(ShellButton *this,int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (this->nLabel == 0) {
    iVar1 = 0;
  }
  else {
    if (param_3 == 0) {
      param_3 = (this->buttonRect).right - (this->buttonRect).left;
    }
    if (param_4 == 0) {
      param_4 = (this->buttonRect).bottom - (this->buttonRect).top;
    }
    (this->labelRect).left = param_1;
    (this->labelRect).top = param_2;
    (this->labelRect).right = param_1 + param_3;
    (this->labelRect).bottom = param_2 + param_4;
    DrawLabelText(this,(char *)0x0);
    iVar1 = 1;
  }
  return iVar1;
}
