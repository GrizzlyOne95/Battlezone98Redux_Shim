/*
 * Entry: 00544c04
 * Name: GetBestDepthFormat
 * Namespace: Global
 * Signature: _D3DFORMAT GetBestDepthFormat(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_D3DFORMAT __cdecl GetBestDepthFormat(void)

{
  _D3DFORMAT _Var1;
  int iVar2;
  uint uVar3;
  
  uVar3 = -(uint)((D3IniFlags & 1U) != 0) & 6;
  do {
    uVar3 = uVar3 - 1;
    if ((int)uVar3 < 0) {
      return D3DFMT_UNKNOWN;
    }
    _Var1 = *(_D3DFORMAT *)(&stack0xffffffe4 + uVar3 * 4);
    iVar2 = (*(d3dappi.lpD3D)->lpVtbl->CheckDeviceFormat)
                      (d3dappi.lpD3D,0,D3DDEVTYPE_HAL,d3dappi.PixelFormat,2,D3DRTYPE_SURFACE,_Var1);
  } while ((iVar2 < 0) ||
          (iVar2 = (*(d3dappi.lpD3D)->lpVtbl->CheckDepthStencilMatch)
                             (d3dappi.lpD3D,0,D3DDEVTYPE_HAL,d3dappi.PixelFormat,d3dappi.PixelFormat
                              ,_Var1), iVar2 < 0));
  return _Var1;
}
