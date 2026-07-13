/*
 * Entry: 00524390
 * Name: ZSORTReset
 * Namespace: Global
 * Signature: int ZSORTReset(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ZSORTReset(void)

{
  memset(SortingTableIndex,0,0xc000);
  maxBucket = 0;
  SortingTableCurrent = SortingTable;
  minBucket = 0xfff;
  return 1;
}
