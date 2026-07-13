/*
 * Entry: 0056fd5b
 * Name: LabelButton::SetButtonMode
 * Namespace: LabelButton
 * Signature: int SetButtonMode(LabelButton * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall LabelButton::SetButtonMode(LabelButton *this,int param_1)

{
  int iVar1;
  
  if (this->nHideFlag == 0) {
    if (param_1 == 0) {
      if (this->nButtonMode != 0) {
        InvalidateRect((HWND)this->hParentHwnd,(RECT *)&this->buttonRect,0);
        InvalidateRect((HWND)this->hButtonHwnd,(RECT *)0x0,0);
        this->nButtonMode = 0;
      }
    }
    else if (param_1 == 1) {
      if (this->nButtonMode != 1) {
        InvalidateRect((HWND)this->hParentHwnd,(RECT *)&this->buttonRect,0);
        InvalidateRect((HWND)this->hButtonHwnd,(RECT *)0x0,0);
        this->nButtonMode = 1;
      }
    }
    else if ((param_1 == 2) && (this->nButtonMode != 2)) {
      InvalidateRect((HWND)this->hParentHwnd,(RECT *)&this->buttonRect,0);
      InvalidateRect((HWND)this->hButtonHwnd,(RECT *)0x0,0);
      this->nButtonMode = 2;
    }
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}
