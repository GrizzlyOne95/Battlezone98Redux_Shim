/*
 * Entry: 0053ff5f
 * Name: D3DAppICreateD3D
 * Namespace: Global
 * Signature: int D3DAppICreateD3D(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3DAppICreateD3D(void)

{
  d3dappi.lpD3D = (IDirect3D9 *)_Direct3DCreate9_4(0x20);
  if (d3dappi.lpD3D == (IDirect3D9 *)0x0) {
    D3DAppErrorToString(LastError);
    D3DAppISetErrorString("Creation of IDirect3D failed.\n%s");
    return 0;
  }
  return 1;
}
