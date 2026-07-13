/*
 * Entry: 004d1572
 * Name: GetNormalPtr
 * Namespace: Global
 * Signature: uchar * GetNormalPtr(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar * __cdecl GetNormalPtr(int param_1,int param_2)

{
  int in_EAX;
  int in_ECX;
  
  return Normals + (in_EAX + 0xc00U & 0x7f) +
                   ((uint)NormalsZoneTable
                          [(in_ECX + 0xc00U & 0x3f80) + ((int)(in_EAX + 0xc00U) >> 7 & 0x7fU)] *
                    0x80 + (in_ECX + 0xc00U & 0x7f)) * 0x80;
}
