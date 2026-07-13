/*
 * Entry: 0056fe28
 * Name: LabelButton::ShowButton
 * Namespace: LabelButton
 * Signature: int ShowButton(LabelButton * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall LabelButton::ShowButton(LabelButton *this)

{
  bool bVar1;
  
  bVar1 = this->nHideFlag != 0;
  if (bVar1) {
    this->nHideFlag = 0;
    ShowWindow((HWND)this->hButtonHwnd,1);
    InvalidateRect((HWND)this->hParentHwnd,(RECT *)&this->buttonRect,0);
    InvalidateRect((HWND)this->hButtonHwnd,(RECT *)0x0,0);
  }
  return (uint)bVar1;
}
