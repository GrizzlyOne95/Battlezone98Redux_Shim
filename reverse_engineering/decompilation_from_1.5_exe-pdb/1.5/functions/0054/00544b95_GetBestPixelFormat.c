/*
 * Entry: 00544b95
 * Name: GetBestPixelFormat
 * Namespace: Global
 * Signature: _D3DFORMAT GetBestPixelFormat(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_D3DFORMAT __cdecl GetBestPixelFormat(void)

{
  _D3DFORMAT _Var1;
  int iVar2;
  int iVar3;
  
  iVar3 = (-(uint)((D3IniFlags & 0x40000U) != 0) & 2) + 2;
  do {
    _Var1 = *(_D3DFORMAT *)(&stack0xffffffe8 + iVar3 * 4);
    iVar2 = (*(d3dappi.lpD3D)->lpVtbl->CheckDeviceType)
                      (d3dappi.lpD3D,0,D3DDEVTYPE_HAL,_Var1,_Var1,d3dappi.bWindowed);
    if (-1 < iVar2) {
      return _Var1;
    }
    iVar3 = iVar3 + -1;
  } while (-1 < iVar3);
  return D3DFMT_UNKNOWN;
}
