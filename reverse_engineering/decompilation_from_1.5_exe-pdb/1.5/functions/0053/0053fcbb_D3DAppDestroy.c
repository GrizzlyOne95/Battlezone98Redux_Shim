/*
 * Entry: 0053fcbb
 * Name: D3DAppDestroy
 * Namespace: Global
 * Signature: int D3DAppDestroy(tagD3DAppInfo * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3DAppDestroy(tagD3DAppInfo *param_1)

{
  ReleaseTLExecuteBuffer();
  if (d3dappi.lpBackBuffer != (IDirect3DSurface9 *)0x0) {
    (*(d3dappi.lpBackBuffer)->lpVtbl->Release)(d3dappi.lpBackBuffer);
    d3dappi.lpBackBuffer = (IDirect3DSurface9 *)0x0;
  }
  if (d3dappi.lpD3DDevice != (IDirect3DDevice9 *)0x0) {
    (*(d3dappi.lpD3DDevice)->lpVtbl->Release)(d3dappi.lpD3DDevice);
    d3dappi.lpD3DDevice = (IDirect3DDevice9 *)0x0;
  }
  if (d3dappi.lpD3D != (IDirect3D9 *)0x0) {
    (*(d3dappi.lpD3D)->lpVtbl->Release)(d3dappi.lpD3D);
    d3dappi.lpD3D = (IDirect3D9 *)0x0;
  }
  d3dappi.hwnd = (HWND__ *)0x0;
  return 1;
}
