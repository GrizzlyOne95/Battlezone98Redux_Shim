/*
 * Entry: 00582006
 * Name: GetCurrentNetworkTime
 * Namespace: Global
 * Signature: ulong GetCurrentNetworkTime(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl GetCurrentNetworkTime(void)

{
  DWORD DVar1;
  
  DVar1 = timeGetTime();
  if (BAddOffset != 0) {
    return DVar1 + dwOffset;
  }
  return DVar1 - dwOffset;
}
