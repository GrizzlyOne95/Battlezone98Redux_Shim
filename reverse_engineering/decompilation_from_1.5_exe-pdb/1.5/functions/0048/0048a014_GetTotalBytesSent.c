/*
 * Entry: 0048a014
 * Name: GetTotalBytesSent
 * Namespace: Global
 * Signature: ulong GetTotalBytesSent(dp_s * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl GetTotalBytesSent(dp_s *param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_1c [4];
  int local_18;
  
  dpGetStats(Net::dp,6,local_1c,0x18);
  iVar2 = local_18;
  dpGetStats(Net::dp,7,local_1c,0x18);
  iVar1 = local_18 * 0x28;
  dpGetStats(Net::dp,4,local_1c,0x18);
  iVar2 = iVar2 + iVar1 + local_18;
  dpGetStats(Net::dp,5,local_1c,0x18);
  return local_18 * 0x28 + iVar2;
}
