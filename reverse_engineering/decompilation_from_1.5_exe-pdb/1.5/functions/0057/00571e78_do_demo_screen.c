/*
 * Entry: 00571e78
 * Name: do_demo_screen
 * Namespace: Global
 * Signature: void do_demo_screen(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl do_demo_screen(int param_1)

{
  HDC hDC;
  ShellBitmap *pSVar1;
  char *pcVar2;
  
  hDC = GetDC((HWND)shell_hwnd);
  pSVar1 = operator_new(0x20);
  if (param_1 == 0) {
    if (pSVar1 == (ShellBitmap *)0x0) goto LAB_00571ebc;
    pcVar2 = "bitmap\\bzonead2.bmp";
  }
  else {
    if (pSVar1 == (ShellBitmap *)0x0) {
LAB_00571ebc:
      pSVar1 = (ShellBitmap *)0x0;
      goto LAB_00571ebe;
    }
    pcVar2 = "bitmap\\bzonead1.bmp";
  }
  pSVar1 = ShellBitmap::ShellBitmap(pSVar1,pcVar2,0,0);
LAB_00571ebe:
  ShellBitmap::BltBitmap(pSVar1,(HDC__ *)hDC);
  if (pSVar1 != (ShellBitmap *)0x0) {
    ShellBitmap::~ShellBitmap(pSVar1);
    operator_delete(pSVar1);
  }
  ReleaseDC((HWND)shell_hwnd,hDC);
  return;
}
