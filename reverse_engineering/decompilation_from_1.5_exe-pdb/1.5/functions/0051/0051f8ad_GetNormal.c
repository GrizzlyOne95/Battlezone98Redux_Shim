/*
 * Entry: 0051f8ad
 * Name: GetNormal
 * Namespace: Global
 * Signature: int GetNormal(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetNormal(int param_1,int param_2)

{
  int in_ECX;
  int in_EDX;
  
  return (uint)Normals[(uint)NormalsZoneTable
                             [((int)(in_EDX + 0xc00U) >> 7) * 0x80 + ((int)(in_ECX + 0xc00U) >> 7)]
                       * 0x4000 + (in_EDX + 0xc00U & 0x7f) * 0x80 + (in_ECX + 0xc00U & 0x7f)];
}
