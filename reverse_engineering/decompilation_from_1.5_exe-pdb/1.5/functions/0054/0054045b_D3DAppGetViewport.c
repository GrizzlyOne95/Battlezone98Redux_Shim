/*
 * Entry: 0054045b
 * Name: D3DAppGetViewport
 * Namespace: Global
 * Signature: void D3DAppGetViewport(ulong * param_1, ulong * param_2, ulong * param_3, ulong * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3DAppGetViewport(ulong *param_1,ulong *param_2,ulong *param_3,ulong *param_4)

{
  _D3DVIEWPORT9 local_1c;
  
  (*(d3dappi.lpD3DDevice)->lpVtbl->GetViewport)(d3dappi.lpD3DDevice,&local_1c);
  *param_1 = local_1c.X;
  *param_2 = local_1c.Y;
  *param_3 = local_1c.Width;
  *param_4 = local_1c.Height;
  return;
}
