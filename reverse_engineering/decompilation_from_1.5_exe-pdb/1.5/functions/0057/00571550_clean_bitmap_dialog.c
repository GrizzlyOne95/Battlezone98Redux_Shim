/*
 * Entry: 00571550
 * Name: clean_bitmap_dialog
 * Namespace: Global
 * Signature: void clean_bitmap_dialog(HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl clean_bitmap_dialog(HDC__ *param_1)

{
  ShellBitmap *pSVar1;
  
  pSVar1 = blankBg;
  if (blankBg != (ShellBitmap *)0x0) {
    ShellBitmap::~ShellBitmap(blankBg);
    operator_delete(pSVar1);
    blankBg = (ShellBitmap *)0x0;
  }
  if (bmBits != (void *)0x0) {
    free(bmBits);
  }
  bmBits = (void *)0x0;
  if (bmInfo != (tagBITMAPINFO *)0x0) {
    free(bmInfo);
  }
  bmInfo = (tagBITMAPINFO *)0x0;
  return;
}
