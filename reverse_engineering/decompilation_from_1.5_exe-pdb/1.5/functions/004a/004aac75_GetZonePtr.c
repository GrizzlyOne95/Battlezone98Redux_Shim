/*
 * Entry: 004aac75
 * Name: GetZonePtr
 * Namespace: Global
 * Signature: ushort * GetZonePtr(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort * __cdecl GetZonePtr(int param_1,int param_2)

{
  return Terrain.Zone_Page_Table
         [((int)(param_1 + 0xc00U) >> 7 & 0x7fU) + (param_2 + 0xc00U & 0x3f80)]->Height +
         (param_2 + 0xc00U & 0x7f) * 0x80 + (param_1 + 0xc00U & 0x7f);
}
