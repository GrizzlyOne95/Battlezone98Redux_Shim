/*
 * Entry: 00543b1e
 * Name: GetTextureMemSize
 * Namespace: Global
 * Signature: ulong GetTextureMemSize(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl GetTextureMemSize(void)

{
  uint uVar1;
  
  uVar1 = (*(d3dappi.lpD3DDevice)->lpVtbl->GetAvailableTextureMem)(d3dappi.lpD3DDevice);
  return uVar1;
}
