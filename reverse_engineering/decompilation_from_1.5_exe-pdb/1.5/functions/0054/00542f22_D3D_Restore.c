/*
 * Entry: 00542f22
 * Name: D3D_Restore
 * Namespace: Global
 * Signature: void D3D_Restore(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3D_Restore(VIDEO_DEVICE *param_1)

{
  if ((d3dappi.lpD3DDevice != (IDirect3DDevice9 *)0x0) &&
     ((UseDDraw != 0 || (D3D_Device_Lost != 0)))) {
    D3DAppIResetDevice();
    return;
  }
  return;
}
