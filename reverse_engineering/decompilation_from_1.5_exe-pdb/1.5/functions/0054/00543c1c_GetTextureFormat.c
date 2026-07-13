/*
 * Entry: 00543c1c
 * Name: GetTextureFormat
 * Namespace: Global
 * Signature: _D3DFORMAT GetTextureFormat(D3DCACHEENTRY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_D3DFORMAT __cdecl GetTextureFormat(D3DCACHEENTRY *param_1)

{
  short sVar1;
  int *in_ECX;
  
  sVar1 = *(short *)(*in_ECX + 2);
  if (sVar1 == 0) {
    if ((D3IniFlags & 0x80000U) != 0) {
      return D3DFMT_X8R8G8B8 - ((*(byte *)((int)in_ECX + 7) & 1) != 0);
    }
    return (uint)((*(byte *)((int)in_ECX + 7) & 1) != 0) * 2 + D3DFMT_R5G6B5;
  }
  if (sVar1 == 1) {
    return (-(uint)((D3IniFlags & 0x80000U) != 0) & 0xfffffffb) + D3DFMT_A4R4G4B4;
  }
  if (sVar1 == 2) {
    return ~((uint)D3IniFlags >> 0x13) & 1 | D3DFMT_X8R8G8B8;
  }
  if (sVar1 == 3) {
    return D3DFMT_A8R8G8B8;
  }
  if (sVar1 == 4) {
    return D3DFMT_X8R8G8B8;
  }
  return D3DFMT_UNKNOWN;
}
