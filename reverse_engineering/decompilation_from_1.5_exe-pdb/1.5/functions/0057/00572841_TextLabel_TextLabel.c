/*
 * Entry: 00572841
 * Name: TextLabel::TextLabel
 * Namespace: TextLabel
 * Signature: TextLabel * TextLabel(TextLabel * this, HWND__ * param_1, char * param_2, int param_3, int param_4, int param_5, int param_6, uint param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TextLabel * __thiscall
TextLabel::TextLabel
          (TextLabel *this,HWND__ *param_1,char *param_2,int param_3,int param_4,int param_5,
          int param_6,uint param_7)

{
  char cVar1;
  int iVar2;
  int iVar3;
  HBITMAP pHVar4;
  HDC hdc;
  HDC hdc_00;
  HGDIOBJ h;
  
  this->hParentHwnd = param_1;
  iVar2 = 4 - (int)param_2;
  do {
    cVar1 = *param_2;
    param_2[(int)this + iVar2] = cVar1;
    iVar3 = defaultFontSize1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  this->nTextVisible = 1;
  SetTextFont(this,defaultFont,iVar3);
  (this->labelRect).left = param_3;
  (this->labelRect).right = param_3 + param_5;
  (this->labelRect).top = param_4;
  (this->labelRect).bottom = param_4 + param_6;
  this->textColor = 0xff00;
  if (param_7 == 0) {
    this->nFormatType = 0x2125;
  }
  else {
    this->nFormatType = param_7;
  }
  pHVar4 = CreateBitmap(param_5,param_6,1,1,(void *)0x0);
  this->hTextBack = (HBITMAP__ *)pHVar4;
  hdc = GetDC((HWND)this->hParentHwnd);
  hdc_00 = CreateCompatibleDC(hdc);
  h = SelectObject(hdc_00,this->hTextBack);
  PatBlt(hdc_00,0,0,param_5,param_6,0xff0062);
  SelectObject(hdc_00,h);
  DeleteObject(hdc_00);
  ReleaseDC((HWND)this->hParentHwnd,hdc);
  return this;
}
