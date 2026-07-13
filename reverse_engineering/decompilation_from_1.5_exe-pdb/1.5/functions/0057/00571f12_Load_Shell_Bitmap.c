/*
 * Entry: 00571f12
 * Name: Load_Shell_Bitmap
 * Namespace: Global
 * Signature: HBITMAP__ * Load_Shell_Bitmap(HWND__ * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HBITMAP__ * __cdecl Load_Shell_Bitmap(HWND__ *param_1,char *param_2)

{
  int iVar1;
  ShellBitmap *this;
  HDC hdc;
  HDC hdc_00;
  HBITMAP h;
  HGDIOBJ h_00;
  DWORD w;
  ShellBitmap *this_00;
  DWORD h_01;
  
  iVar1 = ItemExists(param_2);
  if (iVar1 == 0) {
    return (HBITMAP__ *)0x0;
  }
  this = operator_new(0x20);
  this_00 = (ShellBitmap *)0x0;
  if (this != (ShellBitmap *)0x0) {
    this_00 = ShellBitmap::ShellBitmap(this,param_2,0,0);
  }
  w = (this_00->bmRect).right - (this_00->bmRect).left;
  h_01 = (this_00->bmRect).bottom - (this_00->bmRect).top;
  hdc = GetDC((HWND)param_1);
  hdc_00 = CreateCompatibleDC(hdc);
  h = CreateCompatibleBitmap(hdc,w,h_01);
  h_00 = SelectObject(hdc_00,h);
  SetDIBitsToDevice(hdc_00,0,0,w,h_01,0,0,0,h_01,this_00->bmBits,(BITMAPINFO *)this_00->bmInfo,
                    (uint)((((BITMAPINFO *)this_00->bmInfo)->bmiHeader).biBitCount == 8));
  SelectObject(hdc_00,h_00);
  DeleteObject(hdc_00);
  ReleaseDC((HWND)param_1,hdc);
  ShellBitmap::~ShellBitmap(this_00);
  operator_delete(this_00);
  return (HBITMAP__ *)h;
}
