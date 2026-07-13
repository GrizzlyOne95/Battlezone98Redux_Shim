/*
 * Entry: 0050523a
 * Name: GDI_SetWindowsPalette
 * Namespace: Global
 * Signature: int GDI_SetWindowsPalette(VIDEO_DEVICE * param_1, long param_2, long param_3, RGB * param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
GDI_SetWindowsPalette(VIDEO_DEVICE *param_1,long param_2,long param_3,RGB *param_4,char *param_5)

{
  RGB *pRVar1;
  int iVar2;
  uchar *puVar3;
  uchar *puVar4;
  
  if (param_1->ActiveVideo == 0) {
    iVar2 = 0;
  }
  else {
    memmove(param_1->Palette + param_2,param_4 + param_2,param_3 * 3);
    pRVar1 = param_1->Palette;
    puVar4 = &param_1->Palette[0].g;
    pRVar1->r = '\0';
    *puVar4 = '\0';
    param_1->Palette[0].b = '\0';
    UpdateFloatPalette(pRVar1);
    ApplyGammaToPalette(pRVar1,param_2,param_3,0);
    puVar3 = &Log_Pal.aEntries[0].peGreen;
    do {
      ((tagPALETTEENTRY *)(puVar3 + -1))->peRed = ((RGB *)(puVar4 + -1))->r;
      *puVar3 = *puVar4;
      puVar3[1] = puVar4[1];
      puVar3[2] = '\x04';
      puVar3 = puVar3 + 4;
      puVar4 = puVar4 + 3;
    } while ((int)puVar3 < 0x62e6bd);
    if (hPalette == (HPALETTE__ *)0x0) {
      hPalette = (HPALETTE__ *)CreatePalette((LOGPALETTE *)&Log_Pal);
      hOldPalette = (HPALETTE__ *)SelectPalette((HDC)hWinDC,(HPALETTE)hPalette,0);
    }
    else {
      SetPaletteEntries((HPALETTE)hPalette,0,0x100,(PALETTEENTRY *)Log_Pal.aEntries);
    }
    RealizePalette((HDC)hWinDC);
    Device_Init_Luminance_Table(param_1,param_5);
    iVar2 = 1;
  }
  return iVar2;
}
