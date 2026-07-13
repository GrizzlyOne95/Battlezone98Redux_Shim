/*
 * Entry: 005718c6
 * Name: LabelButton::UpdateButton
 * Namespace: LabelButton
 * Signature: int UpdateButton(LabelButton * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall LabelButton::UpdateButton(LabelButton *this)

{
  int iVar1;
  HDC hDC;
  ulong uVar2;
  
  hDC = GetDC((HWND)this->hParentHwnd);
  if (this->nHideFlag == 0) {
    iVar1 = this->nButtonMode;
    if (iVar1 == 0) {
      uVar2 = 0xb700;
    }
    else {
      if ((iVar1 != 1) && (iVar1 != 2)) goto LAB_005718fb;
      uVar2 = 0xff00;
    }
    DrawButtonBorder(this,uVar2);
  }
LAB_005718fb:
  ReleaseDC((HWND)this->hParentHwnd,hDC);
  return 1;
}
