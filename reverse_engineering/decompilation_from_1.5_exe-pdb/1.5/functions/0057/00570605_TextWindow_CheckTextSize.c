/*
 * Entry: 00570605
 * Name: TextWindow::CheckTextSize
 * Namespace: TextWindow
 * Signature: int CheckTextSize(TextWindow * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextWindow::CheckTextSize(TextWindow *this)

{
  HDC hdc;
  tagRECT local_1c;
  int local_c;
  HGDIOBJ local_8;
  
  local_1c.left = (this->twRect).left;
  local_1c.top = (this->twRect).top;
  local_1c.right = (this->twRect).right;
  local_1c.bottom = (this->twRect).bottom;
  hdc = GetDC((HWND)this->hParentHwnd);
  local_8 = SelectObject(hdc,this->hTextFont);
  local_c = DrawTextExA(hdc,this->textData,-1,&local_1c,this->nFormatType | 0x400,
                        (LPDRAWTEXTPARAMS)0x0);
  SelectObject(hdc,local_8);
  if (local_c <= (this->twRect).bottom - (this->twRect).top) {
    local_c = 0;
  }
  return local_c;
}
