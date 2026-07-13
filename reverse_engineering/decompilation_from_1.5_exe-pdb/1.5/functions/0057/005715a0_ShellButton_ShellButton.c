/*
 * Entry: 005715a0
 * Name: ShellButton::ShellButton
 * Namespace: ShellButton
 * Signature: ShellButton * ShellButton(ShellButton * this, HWND__ * param_1, HINSTANCE__ * param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, char * param_11)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ShellButton * __thiscall
ShellButton::ShellButton
          (ShellButton *this,HWND__ *param_1,HINSTANCE__ *param_2,int param_3,int param_4,
          int param_5,int param_6,int param_7,int param_8,int param_9,int param_10,char *param_11)

{
  char *pcVar1;
  char cVar2;
  HDC hdc;
  HBITMAP pHVar3;
  HDC hdc_00;
  HGDIOBJ h;
  int iVar4;
  
  this->nSoundEffect = 0;
  this->hParentHwnd = param_1;
  this->hCurrentInstance = param_2;
  nDesiredHeight = defaultFontSize1;
  this->nButtonVisible = 1;
  this->nButtonEnable = 1;
  this->textColor = 0xff00;
  hdc = GetDC((HWND)this->hParentHwnd);
  if (param_3 == 0) {
    pHVar3 = CreateBitmap(param_8,param_9,1,1,(void *)0x0);
    this->hButtonOff = (HBITMAP__ *)pHVar3;
    hdc_00 = CreateCompatibleDC(hdc);
    h = SelectObject(hdc_00,this->hButtonOff);
    PatBlt(hdc_00,0,0,param_8,param_9,0xff0062);
    SelectObject(hdc_00,h);
    DeleteObject(hdc_00);
  }
  else {
    pHVar3 = LoadBitmapA((HINSTANCE)param_2,(LPCSTR)(param_3 & 0xffff));
    this->hButtonOff = (HBITMAP__ *)pHVar3;
  }
  pHVar3 = LoadBitmapA((HINSTANCE)param_2,(LPCSTR)(param_4 & 0xffff));
  this->hButtonOn = (HBITMAP__ *)pHVar3;
  pHVar3 = LoadBitmapA((HINSTANCE)param_2,(LPCSTR)(param_5 & 0xffff));
  this->nButtonMode = 0;
  this->hButtonClick = (HBITMAP__ *)pHVar3;
  (this->buttonRect).left = param_6;
  (this->buttonRect).right = param_6 + param_8;
  (this->buttonRect).top = param_7;
  nDesiredHeight = defaultFontSize1;
  (this->buttonRect).bottom = param_7 + param_9;
  iVar4 = 0;
  do {
    pcVar1 = defaultFont + iVar4;
    desiredFont[iVar4] = *pcVar1;
    iVar4 = iVar4 + 1;
  } while (*pcVar1 != '\0');
  EnumFontsA(hdc,defaultFont,EnumButtonFontsProc,2);
  this->hLabelFont = hButtonFont;
  ReleaseDC((HWND)this->hParentHwnd,hdc);
  (this->labelRect).left = (this->buttonRect).left;
  (this->labelRect).top = (this->buttonRect).top;
  (this->labelRect).right = (this->buttonRect).right;
  this->nLabel = param_10;
  (this->labelRect).bottom = (this->buttonRect).bottom;
  if (param_11 == (char *)0x0) {
    builtin_strncpy(this->labelText,"NULL",5);
  }
  else {
    iVar4 = 0x20 - (int)param_11;
    do {
      cVar2 = *param_11;
      param_11[(int)this + iVar4] = cVar2;
      param_11 = param_11 + 1;
    } while (cVar2 != '\0');
  }
  return this;
}
