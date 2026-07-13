/*
 * Entry: 00570e6e
 * Name: do_load_bar
 * Namespace: Global
 * Signature: int do_load_bar(HWND__ * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_load_bar(HWND__ *param_1,int param_2)

{
  HDC hDC;
  HBRUSH hbr;
  RECT local_20;
  LOGBRUSH local_10;
  
  hDC = GetDC((HWND)param_1);
  if (100 < param_2) {
    param_2 = 100;
  }
  local_10.lbStyle = 0;
  local_10.lbHatch = 0;
  local_10.lbColor = 0x9600;
  hbr = CreateBrushIndirect(&local_10);
  local_20.left = 0x84;
  local_20.top = 0x1c8;
  local_20.bottom = 0x1db;
  local_20.right = (param_2 * 0x26) / 10 + 0x84;
  FillRect(hDC,&local_20,hbr);
  if (hbr != (HBRUSH)0x0) {
    DeleteObject(hbr);
  }
  ReleaseDC((HWND)param_1,hDC);
  return 1;
}
