/*
 * Entry: 0056f435
 * Name: ShellButton::HideButton
 * Namespace: ShellButton
 * Signature: int HideButton(ShellButton * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellButton::HideButton(ShellButton *this,int param_1)

{
  int iVar1;
  HDC hdc;
  HDC hdc_00;
  HGDIOBJ h;
  
  if ((this->nButtonVisible == 0) ||
     (this->nButtonVisible = 0, hCurrentBackground == (HBITMAP__ *)0x0)) {
    iVar1 = 0;
  }
  else {
    if (param_1 != 0) {
      hdc = GetDC((HWND)this->hParentHwnd);
      hdc_00 = CreateCompatibleDC(hdc);
      h = SelectObject(hdc_00,hCurrentBackground);
      DrawTransparentBitmap
                ((HDC__ *)hdc,this->hButtonOff,(this->buttonRect).left,(this->buttonRect).top,0,
                 (HDC__ *)hdc_00);
      SelectObject(hdc_00,h);
      DeleteObject(hdc_00);
      ReleaseDC((HWND)this->hParentHwnd,hdc);
    }
    iVar1 = 1;
  }
  return iVar1;
}
