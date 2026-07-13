/*
 * Entry: 0056eb92
 * Name: draw_line_to_button
 * Namespace: Global
 * Signature: void draw_line_to_button(HWND__ * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl draw_line_to_button(HWND__ *param_1,int param_2,int param_3)

{
  HDC hdc;
  HPEN h;
  HGDIOBJ h_00;
  int iStyle;
  COLORREF color;
  POINT local_1c;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  hdc = GetDC((HWND)param_1);
  if (param_3 == 0) {
    color = 0;
    iStyle = 5;
  }
  else {
    color = 0xff00;
    iStyle = 0;
  }
  h = CreatePen(iStyle,2,color);
  h_00 = SelectObject(hdc,h);
  local_1c.y = 0xef;
  local_10 = 0xef;
  local_1c.x = 0x20;
  local_14 = 0x100;
  if (param_2 == 1) {
    local_8 = 99;
  }
  else {
    if (param_2 == 2) {
      local_c = 0x1bd;
      local_8 = 0xc4;
      goto LAB_0056ec38;
    }
    if (param_2 == 3) {
      local_c = 0x1b8;
      local_8 = 0x133;
      goto LAB_0056ec38;
    }
    if (param_2 != 4) goto LAB_0056ec38;
    local_8 = 0x198;
  }
  local_c = 0x184;
LAB_0056ec38:
  Polyline(hdc,&local_1c,3);
  SelectObject(hdc,h_00);
  DeleteObject(h);
  ReleaseDC((HWND)param_1,hdc);
  return;
}
