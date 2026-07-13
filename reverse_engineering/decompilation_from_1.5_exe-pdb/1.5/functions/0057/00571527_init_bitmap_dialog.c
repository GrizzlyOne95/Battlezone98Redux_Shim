/*
 * Entry: 00571527
 * Name: init_bitmap_dialog
 * Namespace: Global
 * Signature: void init_bitmap_dialog(HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl init_bitmap_dialog(HDC__ *param_1)

{
  ShellBitmap *this;
  
  this = operator_new(0x20);
  if (this != (ShellBitmap *)0x0) {
    blankBg = ShellBitmap::ShellBitmap(this,"bitmap\\backgrnd.bmp",0,0);
    return;
  }
  blankBg = (ShellBitmap *)0x0;
  return;
}
