/*
 * Entry: 0056f177
 * Name: DrawTransparentBitmap
 * Namespace: Global
 * Signature: void DrawTransparentBitmap(HDC__ * param_1, HBITMAP__ * param_2, int param_3, int param_4, ulong param_5, HDC__ * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
DrawTransparentBitmap
          (HDC__ *param_1,HBITMAP__ *param_2,int param_3,int param_4,ulong param_5,HDC__ *param_6)

{
  HBITMAP h;
  int iMode;
  HGDIOBJ pvVar1;
  HDC__ *hdcSrc;
  undefined1 local_4c [4];
  int local_48;
  int local_44;
  tagPOINT local_34;
  HGDIOBJ local_2c;
  HGDIOBJ local_28;
  HBITMAP local_24;
  HBITMAP local_20;
  HBITMAP local_1c;
  HDC local_18;
  HDC local_14;
  HDC local_10;
  HDC local_c;
  HDC local_8;
  
  local_8 = CreateCompatibleDC((HDC)param_1);
  SelectObject(local_8,param_2);
  GetObjectA(param_2,0x18,local_4c);
  local_34.x = local_48;
  local_34.y = local_44;
  DPtoLP(local_8,&local_34,1);
  local_14 = CreateCompatibleDC((HDC)param_1);
  local_10 = CreateCompatibleDC((HDC)param_1);
  local_c = CreateCompatibleDC((HDC)param_1);
  local_18 = CreateCompatibleDC((HDC)param_1);
  local_1c = CreateBitmap(local_34.x,local_34.y,1,1,(void *)0x0);
  local_20 = CreateBitmap(local_34.x,local_34.y,1,1,(void *)0x0);
  local_24 = CreateCompatibleBitmap((HDC)param_1,local_34.x,local_34.y);
  h = CreateCompatibleBitmap((HDC)param_1,local_34.x,local_34.y);
  local_1c = SelectObject(local_14,local_1c);
  local_20 = SelectObject(local_10,local_20);
  local_28 = SelectObject(local_c,local_24);
  local_2c = SelectObject(local_18,h);
  iMode = GetMapMode((HDC)param_1);
  SetMapMode(local_8,iMode);
  BitBlt(local_18,0,0,local_34.x,local_34.y,local_8,0,0,0xcc0020);
  local_24 = (HBITMAP)SetBkColor(local_8,param_5);
  BitBlt(local_10,0,0,local_34.x,local_34.y,local_8,0,0,0xcc0020);
  SetBkColor(local_8,(COLORREF)local_24);
  BitBlt(local_14,0,0,local_34.x,local_34.y,local_10,0,0,0x330008);
  hdcSrc = param_1;
  if (param_6 != (HDC__ *)0x0) {
    hdcSrc = param_6;
  }
  BitBlt(local_c,0,0,local_34.x,local_34.y,(HDC)hdcSrc,param_3,param_4,0xcc0020);
  BitBlt(local_c,0,0,local_34.x,local_34.y,local_10,0,0,0x8800c6);
  BitBlt(local_8,0,0,local_34.x,local_34.y,local_14,0,0,0x8800c6);
  BitBlt(local_c,0,0,local_34.x,local_34.y,local_8,0,0,0xee0086);
  BitBlt((HDC)param_1,param_3,param_4,local_34.x,local_34.y,local_c,0,0,0xcc0020);
  BitBlt(local_8,0,0,local_34.x,local_34.y,local_18,0,0,0xcc0020);
  pvVar1 = SelectObject(local_14,local_1c);
  DeleteObject(pvVar1);
  pvVar1 = SelectObject(local_10,local_20);
  DeleteObject(pvVar1);
  pvVar1 = SelectObject(local_c,local_28);
  DeleteObject(pvVar1);
  pvVar1 = SelectObject(local_18,local_2c);
  DeleteObject(pvVar1);
  DeleteDC(local_c);
  DeleteDC(local_14);
  DeleteDC(local_10);
  DeleteDC(local_18);
  DeleteDC(local_8);
  return;
}
