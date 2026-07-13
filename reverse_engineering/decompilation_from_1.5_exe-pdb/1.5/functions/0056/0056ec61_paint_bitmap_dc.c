/*
 * Entry: 0056ec61
 * Name: paint_bitmap_dc
 * Namespace: Global
 * Signature: void paint_bitmap_dc(HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl paint_bitmap_dc(HDC__ *param_1)

{
  DWORD h;
  
  h = (bmInfo->bmiHeader).biHeight;
  SetDIBitsToDevice((HDC)param_1,0,0,(bmInfo->bmiHeader).biWidth,h,0,0,0,h,bmBits,
                    (BITMAPINFO *)bmInfo,(uint)((bmInfo->bmiHeader).biBitCount == 8));
  return;
}
