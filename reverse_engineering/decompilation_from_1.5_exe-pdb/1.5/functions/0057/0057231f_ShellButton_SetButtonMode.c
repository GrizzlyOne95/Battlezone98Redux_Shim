/*
 * Entry: 0057231f
 * Name: ShellButton::SetButtonMode
 * Namespace: ShellButton
 * Signature: int SetButtonMode(ShellButton * this, int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellButton::SetButtonMode(ShellButton *this,int param_1,int param_2,int param_3)

{
  HDC hdc;
  HDC hdc_00;
  HGDIOBJ h;
  int iVar1;
  int iVar2;
  char *pcVar3;
  HDC__ *pHVar4;
  
  iVar2 = 0;
  if (((this->nButtonVisible == 0) || (this->nButtonEnable == 0)) ||
     (hCurrentBackground == (HBITMAP__ *)0x0)) {
    return 0;
  }
  hdc = GetDC((HWND)this->hParentHwnd);
  hdc_00 = CreateCompatibleDC(hdc);
  h = SelectObject(hdc_00,hCurrentBackground);
  if (param_1 == 0) {
    if (this->nButtonMode == 0) goto LAB_005724ae;
    pHVar4 = (HDC__ *)hdc_00;
    if (param_3 != 0) {
      pHVar4 = (HDC__ *)0x0;
    }
    DrawTransparentBitmap
              ((HDC__ *)hdc,this->hButtonOff,(this->buttonRect).left,(this->buttonRect).top,0,pHVar4
              );
    if (this->nLabel != 0) {
      DrawLabelText(this,(char *)0x0);
    }
    this->nButtonMode = 0;
    goto LAB_005724ab;
  }
  if (param_1 == 1) {
    iVar1 = 1;
    if (this->nButtonMode != 1) {
      pHVar4 = (HDC__ *)hdc_00;
      if (param_3 != 0) {
        pHVar4 = (HDC__ *)0x0;
      }
      DrawTransparentBitmap
                ((HDC__ *)hdc,this->hButtonOn,(this->buttonRect).left,(this->buttonRect).top,0,
                 pHVar4);
      if (this->nLabel != 0) {
        DrawLabelText(this,(char *)0x0);
      }
      this->nButtonMode = 1;
      iVar2 = iVar1;
      if (this->nSoundEffect == 0) {
        if (param_2 == 0) goto LAB_005724ae;
        pcVar3 = "cornron.wav";
      }
      else {
        if (param_2 == 0) goto LAB_005724ae;
        pcVar3 = this->sRollFileName;
      }
      ShellPlaySound(pcVar3,100,0,-1);
    }
    goto LAB_005724ae;
  }
  if ((param_1 != 2) || (this->nButtonMode == 2)) goto LAB_005724ae;
  pHVar4 = (HDC__ *)hdc_00;
  if (param_3 != 0) {
    pHVar4 = (HDC__ *)0x0;
  }
  DrawTransparentBitmap
            ((HDC__ *)hdc,this->hButtonClick,(this->buttonRect).left,(this->buttonRect).top,0,pHVar4
            );
  if (this->nLabel != 0) {
    DrawLabelText(this,(char *)0x0);
  }
  this->nButtonMode = 2;
  if (this->nSoundEffect == 0) {
    if (param_2 != 0) {
      pcVar3 = "cornrclk.wav";
      goto LAB_005723f9;
    }
  }
  else if (param_2 != 0) {
    pcVar3 = this->sClickFileName;
LAB_005723f9:
    ShellPlaySound(pcVar3,100,0,-1);
  }
LAB_005724ab:
  iVar2 = 1;
LAB_005724ae:
  SelectObject(hdc_00,h);
  DeleteObject(hdc_00);
  ReleaseDC((HWND)this->hParentHwnd,hdc);
  return iVar2;
}
