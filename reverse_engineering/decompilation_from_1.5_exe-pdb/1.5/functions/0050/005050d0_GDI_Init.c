/*
 * Entry: 005050d0
 * Name: GDI_Init
 * Namespace: Global
 * Signature: int GDI_Init(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl GDI_Init(VIDEO_DEVICE *param_1)

{
  long lVar1;
  BYTE *pBVar2;
  int iVar3;
  int iVar4;
  tagRGBQUAD *ptVar5;
  BYTE *pBVar6;
  tagPALETTEENTRY local_404 [256];
  
  if (param_1->ActiveVideo == 1) {
    GDI_Close(param_1);
  }
  if (hWinDC == (HDC__ *)0x0) {
    hWinDC = (HDC__ *)GetDC((HWND)param_1->hwndApp);
    GetSystemPaletteEntries((HDC)hWinDC,0,0x100,local_404);
    pBVar6 = &DAT_00cd5841;
    pBVar2 = &local_404[0].peGreen;
    do {
      pBVar6[-1] = ((tagPALETTEENTRY *)(pBVar2 + -1))->peRed;
      *pBVar6 = *pBVar2;
      pBVar6[1] = pBVar2[1];
      pBVar6 = pBVar6 + 3;
      pBVar2 = pBVar2 + 4;
    } while ((int)pBVar6 < 0xcd5b41);
    iVar4 = (param_1->Viewport).Height;
    lVar1 = (param_1->Viewport).Width;
    param_1->ActiveVideo = 1;
    param_1->Reserved = &BitmapInfo;
    memset(&BitmapInfo,0,0x428);
    BitmapInfo.bmiHeader.biHeight = -iVar4;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 8;
    BitmapInfo.bmiHeader.biSize = 0x28;
    BitmapInfo.bmiHeader.biCompression = 0;
    ptVar5 = BitmapInfo.bmiColors;
    iVar3 = 0;
    BitmapInfo.bmiHeader.biWidth = lVar1;
    do {
      ptVar5->rgbBlue = (char)(short)iVar3;
      ptVar5->rgbGreen = (char)((ushort)(short)iVar3 >> 8);
      ptVar5 = (tagRGBQUAD *)&ptVar5->rgbRed;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x100);
    (*(param_1->VideoMode).writePaletteEntries)(param_1,0,0x100,(RGB *)&Default_Palette,(char *)0x0)
    ;
    AllocViewport(param_1,lVar1,iVar4);
    if ((param_1->Viewport).Status == 0) {
      param_1->Error = MEMORY_ERROR;
    }
    else {
      Graphic_Buffer_Clear(&param_1->Viewport,0);
      iVar4 = (*(param_1->Refresh).Blit)(param_1);
      if (iVar4 != 0) {
        _VideoMode = 1;
        _DAT_0062db08 = 1;
        _DAT_0062db28 = 1;
        _DAT_0062db48 = 1;
        SOMEONE_KILLED_ResolutionMode = -1;
        ResolutionMode = -1;
        return 1;
      }
    }
  }
  GDI_Close(param_1);
  return 0;
}
