/*
 * Entry: 0056f86d
 * Name: ShellBitmap::LineBlt
 * Namespace: ShellBitmap
 * Signature: void LineBlt(ShellBitmap * this, HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShellBitmap::LineBlt(ShellBitmap *this,HDC__ *param_1)

{
  BITMAPINFO *lpbmi;
  int iVar1;
  UINT cLines;
  HPALETTE hPal;
  int iVar2;
  int xSrc;
  DWORD local_8;
  
  hPal = SelectPalette((HDC)param_1,(HPALETTE)this->pBitmapPal,0);
  RealizePalette((HDC)param_1);
  local_8 = 2;
  if (1 < (this->bmInfo->bmiHeader).biHeight) {
    do {
      lpbmi = (BITMAPINFO *)this->bmInfo;
      iVar2 = (lpbmi->bmiHeader).biWidth;
      iVar1 = (lpbmi->bmiHeader).biHeight;
      xSrc = iVar2 / 2 - (iVar2 * ((int)local_8 / 2)) / iVar1;
      cLines = (lpbmi->bmiHeader).biHeight;
      iVar2 = iVar1 / 2 - (int)local_8 / 2;
      SetDIBitsToDevice((HDC)param_1,(this->bmRect).left + xSrc,(this->bmRect).top + iVar2,
                        (int)((lpbmi->bmiHeader).biWidth * local_8) / (int)cLines,local_8,xSrc,iVar2
                        ,0,cLines,this->bmBits,lpbmi,(uint)((lpbmi->bmiHeader).biBitCount < 9));
      local_8 = local_8 + 2;
    } while ((int)local_8 <= (this->bmInfo->bmiHeader).biHeight);
  }
  SelectPalette((HDC)param_1,hPal,0);
  return;
}
