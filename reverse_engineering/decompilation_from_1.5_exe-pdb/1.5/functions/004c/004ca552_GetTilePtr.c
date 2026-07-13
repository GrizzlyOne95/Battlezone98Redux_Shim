/*
 * Entry: 004ca552
 * Name: GetTilePtr
 * Namespace: Global
 * Signature: ushort * GetTilePtr(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort * __cdecl GetTilePtr(int param_1,int param_2)

{
  return TexelsZoneTable[(param_1 + 0xc00 >> 7 & 0x7fU) + (param_2 + 0xc00U & 0x3f80)] +
         ((int)(param_2 + 0xc00U) / 2 & 0x3fU) * 0x40 + ((param_1 + 0xc00) / 2 & 0x3fU);
}
