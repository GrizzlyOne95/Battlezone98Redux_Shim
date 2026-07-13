/*
 * Entry: 00504fe3
 * Name: GDI_Close
 * Namespace: Global
 * Signature: void GDI_Close(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GDI_Close(VIDEO_DEVICE *param_1)

{
  if (param_1->ActiveVideo != 0) {
    if (hWinDC != (HDC__ *)0x0) {
      SelectObject((HDC)hWinDC,hOldPalette);
      DeleteObject(hPalette);
      Graphic_Buffer_Close(&param_1->Viewport);
      ReleaseDC((HWND)param_1->hwndApp,(HDC)hWinDC);
    }
    hWinDC = (HDC__ *)0x0;
    hPalette = (HPALETTE__ *)0x0;
    param_1->ActiveVideo = 0;
  }
  return;
}
