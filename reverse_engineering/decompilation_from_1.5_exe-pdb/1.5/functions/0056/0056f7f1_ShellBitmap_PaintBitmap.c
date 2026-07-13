/*
 * Entry: 0056f7f1
 * Name: ShellBitmap::PaintBitmap
 * Namespace: ShellBitmap
 * Signature: void PaintBitmap(ShellBitmap * this, HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShellBitmap::PaintBitmap(ShellBitmap *this,HDC__ *param_1)

{
  BITMAPINFO *lpbmi;
  UINT cLines;
  
  lpbmi = (BITMAPINFO *)this->bmInfo;
  cLines = (lpbmi->bmiHeader).biHeight;
  SetDIBitsToDevice((HDC)param_1,(this->bmRect).left,(this->bmRect).top + this->nScanLine,
                    (lpbmi->bmiHeader).biWidth,cLines - this->nScanLine,0,0,0,cLines,this->bmBits,
                    lpbmi,(uint)((lpbmi->bmiHeader).biBitCount < 9));
  return;
}
