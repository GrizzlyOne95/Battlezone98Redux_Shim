/*
 * Entry: 00542afd
 * Name: D3D_Get_DC
 * Namespace: Global
 * Signature: HDC__ * D3D_Get_DC(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HDC__ * __cdecl D3D_Get_DC(VIDEO_DEVICE *param_1)

{
  int iVar1;
  
  iVar1 = hWinRef;
  hWinRef = hWinRef + 1;
  if (iVar1 == 0) {
    (*(d3dappi.lpBackBuffer)->lpVtbl->GetDC)(d3dappi.lpBackBuffer,&hWinDC);
  }
  return hWinDC;
}
