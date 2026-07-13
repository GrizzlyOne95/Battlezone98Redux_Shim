/*
 * Entry: 0056eaea
 * Name: init_bitmap_dc
 * Namespace: Global
 * Signature: void init_bitmap_dc(HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl init_bitmap_dc(HWND__ *param_1)

{
  HDC hDC;
  
  hDC = GetDC((HWND)param_1);
  ReleaseDC((HWND)param_1,hDC);
  return;
}
