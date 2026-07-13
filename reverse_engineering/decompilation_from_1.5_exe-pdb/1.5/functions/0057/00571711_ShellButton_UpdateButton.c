/*
 * Entry: 00571711
 * Name: ShellButton::UpdateButton
 * Namespace: ShellButton
 * Signature: int UpdateButton(ShellButton * this, HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellButton::UpdateButton(ShellButton *this,HDC__ *param_1)

{
  int iVar1;
  HBITMAP__ *pHVar2;
  long lVar3;
  long lVar4;
  
  if (this->nButtonVisible == 0) {
    return 0;
  }
  iVar1 = this->nButtonMode;
  if (iVar1 == 0) {
    lVar4 = (this->buttonRect).top;
    lVar3 = (this->buttonRect).left;
    pHVar2 = this->hButtonOff;
  }
  else if (iVar1 == 1) {
    lVar4 = (this->buttonRect).top;
    lVar3 = (this->buttonRect).left;
    pHVar2 = this->hButtonOn;
  }
  else {
    if (iVar1 != 2) goto LAB_00571763;
    lVar4 = (this->buttonRect).top;
    lVar3 = (this->buttonRect).left;
    pHVar2 = this->hButtonClick;
  }
  DrawTransparentBitmap(param_1,pHVar2,lVar3,lVar4,0,(HDC__ *)0x0);
LAB_00571763:
  if (this->nLabel != 0) {
    DrawLabelText(this,param_1,(char *)0x0);
  }
  return 1;
}
