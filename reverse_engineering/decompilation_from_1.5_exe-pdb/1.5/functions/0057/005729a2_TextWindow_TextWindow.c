/*
 * Entry: 005729a2
 * Name: TextWindow::TextWindow
 * Namespace: TextWindow
 * Signature: TextWindow * TextWindow(TextWindow * this, HWND__ * param_1, char * param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TextWindow * __thiscall
TextWindow::TextWindow
          (TextWindow *this,HWND__ *param_1,char *param_2,int param_3,int param_4,int param_5,
          int param_6,int param_7)

{
  char cVar1;
  uint uVar2;
  HBITMAP pHVar3;
  HDC hdc;
  HDC hdc_00;
  HGDIOBJ h;
  int iVar4;
  
  this->hParentHwnd = param_1;
  this->_padding_ = (int)&_vftable_;
  iVar4 = (int)this->textData - (int)param_2;
  do {
    cVar1 = *param_2;
    param_2[iVar4] = cVar1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  uVar2 = Hash(this->textData,0x811c9dc5);
  iVar4 = defaultFontSize1;
  this->textHash = uVar2;
  this->nTextVisible = 1;
  SetTextFont(this,defaultFont,iVar4);
  this->nScrollNum = 0;
  (this->twRect).left = param_3;
  (this->twRect).right = param_3 + param_5;
  (this->twRect).top = param_4;
  this->textColor = 0xff00;
  (this->twRect).bottom = param_4 + param_6;
  this->nFormatType = 0x2050;
  pHVar3 = CreateBitmap(param_5,param_6,1,1,(void *)0x0);
  this->hTextBack = (HBITMAP__ *)pHVar3;
  hdc = GetDC((HWND)this->hParentHwnd);
  hdc_00 = CreateCompatibleDC(hdc);
  h = SelectObject(hdc_00,this->hTextBack);
  PatBlt(hdc_00,0,0,param_5,param_6,0xff0062);
  SelectObject(hdc_00,h);
  DeleteObject(hdc_00);
  ReleaseDC((HWND)this->hParentHwnd,hdc);
  return this;
}
