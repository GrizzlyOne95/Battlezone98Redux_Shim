/*
 * Entry: 005708f8
 * Name: TabTextWindow::DrawWindowText
 * Namespace: TabTextWindow
 * Signature: int DrawWindowText(TabTextWindow * this, HDC__ * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TabTextWindow::DrawWindowText(TabTextWindow *this,HDC__ *param_1,int param_2)

{
  int iVar1;
  tagDRAWTEXTPARAMS local_48;
  tagRECT local_34;
  int local_24;
  int local_20;
  HGDIOBJ local_1c;
  HBITMAP local_18;
  HGDIOBJ local_14;
  HGDIOBJ local_10;
  HDC local_c;
  HDC local_8;
  
  if (hCurrentBackground == (HBITMAP__ *)0x0) {
    iVar1 = 0;
  }
  else {
    local_c = CreateCompatibleDC((HDC)param_1);
    local_1c = SelectObject(local_c,hCurrentBackground);
    local_8 = CreateCompatibleDC((HDC)param_1);
    iVar1 = this->_padding_ - this->_padding_;
    local_20 = this->_padding_ - this->_padding_;
    local_24 = iVar1;
    local_18 = CreateCompatibleBitmap((HDC)param_1,iVar1,local_20);
    local_14 = SelectObject(local_8,local_18);
    BitBlt(local_8,0,0,iVar1,local_20,local_c,this->_padding_,this->_padding_,0xcc0020);
    local_10 = SelectObject(local_8,(HGDIOBJ)this->_padding_);
    SetBkMode(local_8,1);
    SetTextColor(local_8,this->_padding_);
    if (this->_padding_ != 0) {
      local_48.iLeftMargin = 0;
      local_48.iRightMargin = 0;
      local_34.left = 0;
      local_34.top = 0;
      local_48.uiLengthDrawn = 0;
      local_34.right = local_24;
      local_34.bottom = local_20;
      this->_padding_ = 0xc0;
      local_48.cbSize = 0x14;
      local_48.iTabLength = 0x19;
      DrawTextExA(local_8,(LPSTR)&this->_padding_,-1,&local_34,0xc0,&local_48);
      iVar1 = local_24;
    }
    BitBlt((HDC)param_1,this->_padding_,this->_padding_,iVar1,local_20,local_8,0,0,0xcc0020);
    if (local_10 != (HGDIOBJ)0x0) {
      SelectObject(local_8,local_10);
    }
    hButtonFont = (HFONT__ *)0x0;
    SelectObject(local_8,local_14);
    DeleteObject(local_18);
    DeleteObject(local_8);
    SelectObject(local_c,local_1c);
    DeleteObject(local_c);
    iVar1 = 1;
  }
  return iVar1;
}
