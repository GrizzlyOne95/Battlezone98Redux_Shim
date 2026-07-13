/*
 * Entry: 005217bf
 * Name: GetLuma256
 * Namespace: Global
 * Signature: uchar GetLuma256(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl GetLuma256(int param_1,int param_2)

{
  uchar *puVar1;
  int unaff_retaddr;
  
  puVar1 = GetNormalPtr(unaff_retaddr,param_1);
  return *puVar1;
}
