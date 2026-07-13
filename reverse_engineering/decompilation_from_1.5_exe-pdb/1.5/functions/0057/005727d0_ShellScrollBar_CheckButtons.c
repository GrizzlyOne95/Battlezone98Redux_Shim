/*
 * Entry: 005727d0
 * Name: ShellScrollBar::CheckButtons
 * Namespace: ShellScrollBar
 * Signature: int CheckButtons(ShellScrollBar * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellScrollBar::CheckButtons(ShellScrollBar *this,int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = check_roll_over(&this->lRect,param_1,param_2);
  if (iVar1 == 0) {
    iVar1 = check_roll_over(&this->rRect,param_1,param_2);
    if (iVar1 == 0) {
      return -1;
    }
    ScrollUp(this);
  }
  else {
    ScrollDown(this);
  }
  if (this->nSoundEnable != 0) {
    ShellPlaySound("arrowclk.wav",100,0,-1);
  }
  return this->nCurrentPos;
}
