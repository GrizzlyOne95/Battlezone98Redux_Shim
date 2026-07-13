/*
 * Entry: 0050532c
 * Name: GDI_OverlayPalette
 * Namespace: Global
 * Signature: int GDI_OverlayPalette(VIDEO_DEVICE * param_1, RGB * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GDI_OverlayPalette(VIDEO_DEVICE *param_1,RGB *param_2)

{
  uchar *puVar1;
  uchar *puVar2;
  
  if (param_1->ActiveVideo == 0) {
    return 0;
  }
  puVar1 = &Log_Pal.aEntries[0].peGreen;
  puVar2 = &param_2->b;
  do {
    ((tagPALETTEENTRY *)(puVar1 + -1))->peRed = ((RGB *)(puVar2 + -2))->r;
    *puVar1 = puVar2[-1];
    puVar1[1] = *puVar2;
    puVar1[2] = '\x04';
    puVar1 = puVar1 + 4;
    puVar2 = puVar2 + 3;
  } while ((int)puVar1 < 0x62e6bd);
  if (hPalette == (HPALETTE__ *)0x0) {
    hPalette = (HPALETTE__ *)CreatePalette((LOGPALETTE *)&Log_Pal);
    hOldPalette = (HPALETTE__ *)SelectPalette((HDC)hWinDC,(HPALETTE)hPalette,0);
  }
  else {
    SetPaletteEntries((HPALETTE)hPalette,0,0x100,(PALETTEENTRY *)Log_Pal.aEntries);
  }
  return 1;
}
