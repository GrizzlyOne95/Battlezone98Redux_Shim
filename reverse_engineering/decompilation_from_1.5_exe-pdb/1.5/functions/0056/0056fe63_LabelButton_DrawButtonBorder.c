/*
 * Entry: 0056fe63
 * Name: LabelButton::DrawButtonBorder
 * Namespace: LabelButton
 * Signature: void DrawButtonBorder(LabelButton * this, ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LabelButton::DrawButtonBorder(LabelButton *this,ulong param_1)

{
  HDC hdc;
  HGDIOBJ h;
  POINT local_30;
  long local_28;
  long local_24;
  long local_20;
  long local_1c;
  long local_18;
  long local_14;
  long local_10;
  long local_c;
  HPEN local_8;
  
  hdc = GetDC((HWND)this->hParentHwnd);
  local_8 = CreatePen(0,1,param_1);
  h = SelectObject(hdc,local_8);
  local_30.x = (this->buttonRect).left;
  local_30.y = (this->buttonRect).top;
  local_28 = (this->buttonRect).right;
  local_1c = (this->buttonRect).bottom;
  local_24 = local_30.y;
  local_20 = local_28;
  local_18 = local_30.x;
  local_14 = local_1c;
  local_10 = local_30.x;
  local_c = local_30.y;
  Polyline(hdc,&local_30,5);
  SelectObject(hdc,h);
  ReleaseDC((HWND)this->hParentHwnd,hdc);
  DeleteObject(local_8);
  return;
}
