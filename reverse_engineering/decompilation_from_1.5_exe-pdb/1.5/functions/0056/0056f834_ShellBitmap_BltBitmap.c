/*
 * Entry: 0056f834
 * Name: ShellBitmap::BltBitmap
 * Namespace: ShellBitmap
 * Signature: void BltBitmap(ShellBitmap * this, HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShellBitmap::BltBitmap(ShellBitmap *this,HDC__ *param_1)

{
  BITMAPINFO *lpbmi;
  DWORD h;
  
  lpbmi = (BITMAPINFO *)this->bmInfo;
  h = (lpbmi->bmiHeader).biHeight;
  SetDIBitsToDevice((HDC)param_1,(this->bmRect).left,(this->bmRect).top,(lpbmi->bmiHeader).biWidth,h
                    ,0,0,0,h,this->bmBits,lpbmi,(uint)((lpbmi->bmiHeader).biBitCount < 9));
  return;
}
