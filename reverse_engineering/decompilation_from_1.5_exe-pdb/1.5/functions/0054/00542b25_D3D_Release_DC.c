/*
 * Entry: 00542b25
 * Name: D3D_Release_DC
 * Namespace: Global
 * Signature: void D3D_Release_DC(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3D_Release_DC(VIDEO_DEVICE *param_1)

{
  hWinRef = hWinRef + -1;
  if (hWinRef == 0) {
    (*(d3dappi.lpBackBuffer)->lpVtbl->ReleaseDC)(d3dappi.lpBackBuffer,hWinDC);
    hWinDC = (HDC__ *)0x0;
  }
  return;
}
