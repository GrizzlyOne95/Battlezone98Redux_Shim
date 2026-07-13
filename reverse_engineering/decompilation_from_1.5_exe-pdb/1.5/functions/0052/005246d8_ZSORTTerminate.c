/*
 * Entry: 005246d8
 * Name: ZSORTTerminate
 * Namespace: Global
 * Signature: void ZSORTTerminate(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ZSORTTerminate(void)

{
  if (SortingTable != (_ZSORTING *)0x0) {
    VirtualFree(SortingTable,0,0x8000);
  }
  if (SortingTableIndex != (_ZSORTINGAMOUNT *)0x0) {
    VirtualFree(SortingTableIndex,0,0x8000);
  }
  SortingTable = (_ZSORTING *)0x0;
  SortingTableIndex = (_ZSORTINGAMOUNT *)0x0;
  maxBucket = 0;
  minBucket = 0xfff;
  return;
}
