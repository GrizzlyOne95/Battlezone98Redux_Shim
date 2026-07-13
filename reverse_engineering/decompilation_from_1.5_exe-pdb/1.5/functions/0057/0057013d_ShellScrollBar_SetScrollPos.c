/*
 * Entry: 0057013d
 * Name: ShellScrollBar::SetScrollPos
 * Namespace: ShellScrollBar
 * Signature: int SetScrollPos(ShellScrollBar * this, HDC__ * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellScrollBar::SetScrollPos(ShellScrollBar *this,HDC__ *param_1,int param_2)

{
  int iVar1;
  HDC hdc;
  POINT local_20;
  int local_18;
  int local_14;
  HGDIOBJ local_10;
  HGDIOBJ local_c;
  HPEN local_8;
  
  if (hCurrentBackground == (HBITMAP__ *)0x0) {
    iVar1 = 0;
  }
  else {
    local_8 = CreatePen(0,4,0xff00);
    hdc = CreateCompatibleDC((HDC)param_1);
    local_c = SelectObject(hdc,hCurrentBackground);
    DrawTransparentBitmap
              (param_1,this->hScrollBitmap,(this->scRect).left,(this->scRect).top,0,(HDC__ *)hdc);
    local_10 = SelectObject((HDC)param_1,local_8);
    if (this->nRange < param_2) {
      param_2 = this->nRange;
    }
    if (param_2 < 0) {
      param_2 = 0;
    }
    if (this->nOrientation == 0) {
      local_20.x = (this->lRect).right;
      local_14 = ((this->scRect).bottom - (this->scRect).top) / 2 + (this->scRect).top;
      local_18 = this->nSectionSize * param_2 + local_20.x;
      local_20.y = local_14;
    }
    else {
      local_20.y = (this->lRect).bottom;
      local_20.x = ((this->scRect).right - (this->scRect).left) / 2 + (this->lRect).right;
      local_14 = this->nSectionSize * param_2 + local_20.y;
      local_18 = local_20.x;
    }
    Polyline((HDC)param_1,&local_20,2);
    SelectObject(hdc,local_c);
    DeleteObject(hdc);
    SelectObject((HDC)param_1,local_10);
    DeleteObject(local_8);
    this->nCurrentPos = param_2;
    iVar1 = 1;
  }
  return iVar1;
}
