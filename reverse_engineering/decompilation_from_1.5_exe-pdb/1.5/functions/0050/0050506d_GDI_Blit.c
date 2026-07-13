/*
 * Entry: 0050506d
 * Name: GDI_Blit
 * Namespace: Global
 * Signature: int GDI_Blit(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GDI_Blit(VIDEO_DEVICE *param_1)

{
  DWORD h;
  int iVar1;
  
  if (param_1->ActiveVideo != 0) {
    Repair_Buffer_Edge(param_1);
    h = (param_1->Viewport).Height;
    iVar1 = SetDIBitsToDevice((HDC)hWinDC,0,0,(param_1->Viewport).Width,h,0,0,0,h,
                              (param_1->Viewport).Buffer,(BITMAPINFO *)&BitmapInfo,1);
    if (iVar1 != 0) {
      return 1;
    }
    param_1->Error = GDI_BLIT_ERROR;
  }
  return 0;
}
