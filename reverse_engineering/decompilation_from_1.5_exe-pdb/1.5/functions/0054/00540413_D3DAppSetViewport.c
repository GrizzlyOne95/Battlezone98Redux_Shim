/*
 * Entry: 00540413
 * Name: D3DAppSetViewport
 * Namespace: Global
 * Signature: void D3DAppSetViewport(ulong param_1, ulong param_2, ulong param_3, ulong param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3DAppSetViewport(ulong param_1,ulong param_2,ulong param_3,ulong param_4)

{
  _D3DVIEWPORT9 local_1c;
  
  local_1c.MinZ = 0.0;
  local_1c.X = param_1;
  local_1c.MaxZ = 1.0;
  local_1c.Y = param_2;
  local_1c.Width = param_3;
  local_1c.Height = param_4;
  RenderExB(d3dappi.lpD3DDevice);
  (*(d3dappi.lpD3DDevice)->lpVtbl->SetViewport)(d3dappi.lpD3DDevice,&local_1c);
  return;
}
