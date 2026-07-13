/*
 * Entry: 0056eb02
 * Name: draw_cursor
 * Namespace: Global
 * Signature: void draw_cursor(HWND__ * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl draw_cursor(HWND__ *param_1,int param_2,int param_3)

{
  HDC hdc;
  POINT local_2c;
  int local_24;
  undefined4 local_20;
  POINT local_1c;
  undefined4 local_14;
  int local_10;
  HPEN local_c;
  HGDIOBJ local_8;
  
  hdc = GetDC((HWND)param_1);
  local_c = CreatePen(0,2,0xff00);
  local_8 = SelectObject(hdc,local_c);
  local_1c.y = param_3;
  local_10 = param_3;
  local_2c.x = param_2;
  local_24 = param_2;
  local_1c.x = 0;
  local_2c.y = 0;
  local_14 = 0x280;
  local_20 = 0x1e0;
  Polyline(hdc,&local_1c,2);
  Polyline(hdc,&local_2c,2);
  SelectObject(hdc,local_8);
  DeleteObject(local_c);
  ReleaseDC((HWND)param_1,hdc);
  return;
}
