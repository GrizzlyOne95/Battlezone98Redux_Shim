/*
 * Entry: 0056fff8
 * Name: ShellScrollBar::ShellScrollBar
 * Namespace: ShellScrollBar
 * Signature: ShellScrollBar * ShellScrollBar(ShellScrollBar * this, HWND__ * param_1, HINSTANCE__ * param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ShellScrollBar * __thiscall
ShellScrollBar::ShellScrollBar
          (ShellScrollBar *this,HWND__ *param_1,HINSTANCE__ *param_2,int param_3,int param_4,
          int param_5,int param_6,int param_7,int param_8,int param_9)

{
  HBITMAP pHVar1;
  HDC hdc;
  HDC hdc_00;
  HGDIOBJ h;
  int iVar2;
  int iVar3;
  
  this->hParentHwnd = param_1;
  this->hInstance = param_2;
  pHVar1 = LoadBitmapA((HINSTANCE)param_2,(LPCSTR)(param_3 & 0xffff));
  this->hScrollBitmap = (HBITMAP__ *)pHVar1;
  iVar2 = param_6 + param_4;
  iVar3 = param_7 + param_5;
  this->nOrientation = param_9;
  (this->scRect).left = param_4;
  (this->scRect).top = param_5;
  (this->scRect).right = iVar2;
  (this->scRect).bottom = iVar3;
  this->nSoundEnable = 1;
  (this->lRect).left = param_4;
  (this->lRect).top = param_5;
  (this->rRect).right = iVar2;
  (this->rRect).bottom = iVar3;
  if (param_9 == 0) {
    (this->lRect).right = param_8 + param_4;
    param_4 = (param_4 - param_8) + param_6;
    (this->lRect).bottom = iVar3;
  }
  else {
    iVar3 = param_8 + param_5;
    (this->lRect).right = iVar2;
    param_5 = (param_5 - param_8) + param_7;
    (this->lRect).bottom = iVar3;
  }
  (this->rRect).left = param_4;
  (this->rRect).top = param_5;
  iVar2 = param_6 + param_8 * -2;
  this->nLength = iVar2;
  this->nCurrentPos = 0;
  this->nRange = 10;
  this->nSectionSize = iVar2 / 10;
  pHVar1 = CreateBitmap(param_6,param_7,1,1,(void *)0x0);
  this->hBitmap = (HBITMAP__ *)pHVar1;
  hdc = GetDC((HWND)this->hParentHwnd);
  hdc_00 = CreateCompatibleDC(hdc);
  h = SelectObject(hdc_00,this->hBitmap);
  PatBlt(hdc_00,0,0,param_6,param_7,0xff0062);
  SelectObject(hdc_00,h);
  DeleteObject(hdc_00);
  ReleaseDC((HWND)this->hParentHwnd,hdc);
  return this;
}
