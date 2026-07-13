/*
 * Entry: 0053fc86
 * Name: D3DAppDestroy3DOnly
 * Namespace: Global
 * Signature: int D3DAppDestroy3DOnly(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3DAppDestroy3DOnly(void)

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
  return 1;
}
