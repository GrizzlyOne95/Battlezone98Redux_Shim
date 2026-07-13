/*
 * Entry: 0056fdea
 * Name: LabelButton::HideButton
 * Namespace: LabelButton
 * Signature: int HideButton(LabelButton * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall LabelButton::HideButton(LabelButton *this)

{
  bool bVar1;
  
  bVar1 = this->nHideFlag == 0;
  if (bVar1) {
    this->nHideFlag = 1;
    ShowWindow((HWND)this->hButtonHwnd,0);
    InvalidateRect((HWND)this->hParentHwnd,(RECT *)&this->buttonRect,0);
    InvalidateRect((HWND)this->hButtonHwnd,(RECT *)0x0,0);
  }
  return (uint)bVar1;
}
