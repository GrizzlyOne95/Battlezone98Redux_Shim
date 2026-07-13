/*
 * Entry: 005706ab
 * Name: TextWindow::DrawWindowText
 * Namespace: TextWindow
 * Signature: int DrawWindowText(TextWindow * this, HDC__ * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextWindow::DrawWindowText(TextWindow *this,HDC__ *param_1,int param_2)

{
  int iVar1;
  HDC hdc;
  int iVar2;
  tagRECT local_38;
  int local_28;
  int local_24;
  HGDIOBJ local_20;
  HBITMAP local_1c;
  HGDIOBJ local_18;
  int local_14;
  HGDIOBJ local_10;
  tagRECT *local_c;
  HDC local_8;
  
  local_38.left = (this->twRect).left;
  local_38.top = (this->twRect).top;
  local_38.right = (this->twRect).right;
  local_38.bottom = (this->twRect).bottom;
  if (hCurrentBackground == (HBITMAP__ *)0x0) {
    iVar1 = 0;
  }
  else {
    this->nScrollNum = this->nScrollNum + param_2;
    local_14 = (this->twRect).right - (this->twRect).left;
    iVar1 = (this->twRect).bottom - (this->twRect).top;
    local_8 = CreateCompatibleDC((HDC)param_1);
    local_20 = SelectObject(local_8,hCurrentBackground);
    hdc = CreateCompatibleDC((HDC)param_1);
    local_c = &this->twRect;
    local_28 = (this->twRect).right - local_c->left;
    local_24 = (this->twRect).bottom - (this->twRect).top;
    local_1c = CreateCompatibleBitmap((HDC)param_1,local_28,local_24);
    local_18 = SelectObject(hdc,local_1c);
    BitBlt(hdc,0,0,local_28,local_24,local_8,local_c->left,(this->twRect).top,0xcc0020);
    local_10 = SelectObject(hdc,this->hTextFont);
    SetBkMode(hdc,1);
    SetTextColor(hdc,this->textColor);
    if (this->nTextVisible != 0) {
      local_38.left = 0;
      local_38.top = 0;
      local_38.right = local_14;
      local_38.bottom = iVar1;
      iVar2 = DrawTextExA(hdc,this->textData,-1,&local_38,this->nFormatType | 0x400,
                          (LPDRAWTEXTPARAMS)0x0);
      if (iVar1 < iVar2) {
        iVar2 = iVar2 - iVar1;
      }
      else {
        iVar2 = 0;
      }
      if (this->nScrollNum < 0) {
        this->nScrollNum = 0;
      }
      if (iVar2 < this->nScrollNum) {
        this->nScrollNum = iVar2;
      }
      local_38.top = local_38.top - this->nScrollNum;
      local_38.bottom = local_38.bottom - this->nScrollNum;
      DrawTextExA(hdc,this->textData,-1,&local_38,this->nFormatType,(LPDRAWTEXTPARAMS)0x0);
    }
    BitBlt((HDC)param_1,local_c->left,(this->twRect).top,local_28,local_24,hdc,0,0,0xcc0020);
    if (local_10 != (HGDIOBJ)0x0) {
      SelectObject(hdc,local_10);
    }
    hButtonFont = (HFONT__ *)0x0;
    SelectObject(hdc,local_18);
    DeleteObject(local_1c);
    DeleteObject(hdc);
    SelectObject(local_8,local_20);
    DeleteObject(local_8);
    iVar1 = 1;
  }
  return iVar1;
}
