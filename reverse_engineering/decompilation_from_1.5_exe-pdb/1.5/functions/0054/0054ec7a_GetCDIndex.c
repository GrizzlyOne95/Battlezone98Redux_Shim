/*
 * Entry: 0054ec7a
 * Name: GetCDIndex
 * Namespace: Global
 * Signature: long GetCDIndex(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl GetCDIndex(void)

{
  FindCDByName("BZONE",0);
  return CDIndex;
}
