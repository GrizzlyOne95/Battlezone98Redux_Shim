/*
 * Entry: 00542fcd
 * Name: D3D_Clear
 * Namespace: Global
 * Signature: int D3D_Clear(VIDEO_DEVICE * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3D_Clear(VIDEO_DEVICE *param_1,long param_2)

{
  (*(d3dappi.lpD3DDevice)->lpVtbl->Clear)(d3dappi.lpD3DDevice,0,(_D3DRECT *)0x0,1,param_2,1.0,0);
  return 1;
}
