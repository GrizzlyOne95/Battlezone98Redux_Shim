/*
 * Entry: 00570a81
 * Name: draw_border
 * Namespace: Global
 * Signature: void draw_border(HWND__ * param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl draw_border(HWND__ *param_1,int param_2,int param_3,int param_4,int param_5)

{
  POINT local_38;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  HGDIOBJ local_10;
  HPEN local_c;
  HDC local_8;
  
  local_c = CreatePen(0,1,0xff00);
  local_8 = GetDC((HWND)param_1);
  local_10 = SelectObject(local_8,local_c);
  local_38.x = param_2 + -1;
  local_30 = param_2 + 1 + param_4;
  local_24 = param_3 + 1 + param_5;
  local_38.y = param_3 + -1;
  local_2c = local_38.y;
  local_28 = local_30;
  local_20 = local_38.x;
  local_1c = local_24;
  local_18 = local_38.x;
  local_14 = local_38.y;
  Polyline(local_8,&local_38,5);
  SelectObject(local_8,local_10);
  ReleaseDC((HWND)param_1,local_8);
  DeleteObject(local_c);
  return;
}
