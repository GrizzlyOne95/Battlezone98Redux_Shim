/*
 * Entry: 00570cce
 * Name: SetCurrentBackground
 * Namespace: Global
 * Signature: void SetCurrentBackground(HWND__ * param_1, ShellBitmap * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetCurrentBackground(HWND__ *param_1,ShellBitmap *param_2)

{
  HDC hdc;
  HDC hdc_00;
  HGDIOBJ h;
  
  if (hCurrentBackground != (HBITMAP__ *)0x0) {
    DeleteObject(hCurrentBackground);
    hCurrentBackground = (HBITMAP__ *)0x0;
  }
  hdc = GetDC((HWND)param_1);
  hdc_00 = CreateCompatibleDC(hdc);
  hCurrentBackground = (HBITMAP__ *)CreateCompatibleBitmap(hdc,0x280,0x1e0);
  hCurrentHwnd = param_1;
  h = SelectObject(hdc_00,hCurrentBackground);
  if (param_2 == (ShellBitmap *)0x0) {
    BitBlt(hdc_00,0,0,0x280,0x1e0,hdc,0,0,0xcc0020);
  }
  else {
    SetDIBitsToDevice(hdc_00,0,0,0x280,0x1e0,0,0,0,0x1e0,param_2->bmBits,
                      (BITMAPINFO *)param_2->bmInfo,
                      (uint)((((BITMAPINFO *)param_2->bmInfo)->bmiHeader).biBitCount == 8));
  }
  SelectObject(hdc_00,h);
  DeleteObject(hdc_00);
  ReleaseDC((HWND)param_1,hdc);
  return;
}
