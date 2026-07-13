/*
 * Entry: 005053af
 * Name: GDI_ChangeMode
 * Namespace: Global
 * Signature: int GDI_ChangeMode(VIDEO_DEVICE * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GDI_ChangeMode(VIDEO_DEVICE *param_1,long param_2)

{
  tagRECT *lpRect;
  int iVar1;
  HWND hWnd;
  int iVar2;
  int cx;
  int X;
  int cy;
  
  SOMEONE_KILLED_ResolutionMode = param_2;
  ResolutionMode = param_2;
  iVar2 = *(int *)(&DAT_0062da80 + param_2 * 0x20);
  iVar1 = *(int *)(&DAT_0062da84 + param_2 * 0x20);
  Graphic_Buffer_Close(&param_1->Viewport);
  AllocViewport(param_1,iVar2,iVar1);
  if ((param_1->Viewport).Status == 0) {
    param_1->Error = MEMORY_ERROR;
    GDI_Close(param_1);
    iVar2 = 0;
  }
  else {
    BitmapInfo.bmiHeader.biWidth = (param_1->Viewport).Width;
    BitmapInfo.bmiHeader.biHeight = -(param_1->Viewport).Height;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biCompression = 0;
    BitmapInfo.bmiHeader.biBitCount = 8;
    lpRect = &param_1->winRect;
    lpRect->left = 0;
    (param_1->winRect).top = 0;
    (param_1->winRect).right = iVar2;
    (param_1->winRect).bottom = iVar1;
    param_1->Client_Width = iVar2;
    param_1->Client_Height = iVar1;
    if (((param_1->Screen_Height == iVar1) && (param_1->Screen_Width == iVar2)) && (param_2 == 5)) {
      (param_1->VideoMode).windowStyle = -0x80000000;
    }
    else {
      (param_1->VideoMode).windowStyle = 0xce0000;
    }
    AdjustWindowRect((LPRECT)lpRect,(param_1->VideoMode).windowStyle,0);
    SetWindowLongA((HWND)param_1->hwndApp,-0x10,(param_1->VideoMode).windowStyle | 0x10000000);
    cx = (param_1->winRect).right - lpRect->left;
    cy = (param_1->winRect).bottom - (param_1->winRect).top;
    X = param_1->Screen_Width - cx >> 1;
    lpRect->left = X;
    (param_1->Viewport).Pane.y1 = iVar1 + -1;
    hWnd = (HWND)param_1->hwndApp;
    (param_1->winRect).right = cx;
    (param_1->winRect).bottom = cy;
    (param_1->Viewport).Pane.x1 = iVar2 + -1;
    (param_1->winRect).top = 0;
    SetWindowPos(hWnd,(HWND)0x0,X,0,cx,cy,0x40);
    RealizePalette((HDC)hWinDC);
    SynchCamera();
    iVar2 = 1;
  }
  return iVar2;
}
