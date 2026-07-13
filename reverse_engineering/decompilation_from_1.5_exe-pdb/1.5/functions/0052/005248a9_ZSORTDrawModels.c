/*
 * Entry: 005248a9
 * Name: ZSORTDrawModels
 * Namespace: Global
 * Signature: void ZSORTDrawModels(CAMERA * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ZSORTDrawModels(CAMERA *param_1,int param_2)

{
  int iVar1;
  
  SortingTableIndexLift = SortingTableIndex + maxBucket;
  for (iVar1 = (maxBucket - minBucket) + 1; 0 < iVar1; iVar1 = iVar1 + -1) {
    if (0 < SortingTableIndexLift->EntrieAmount) {
      SortingTableLift = SortingTableIndexLift->Entrie;
      do {
        if (SortingTableLift->Type == 6) {
          (*SortRender[6])(SortingTableLift,param_1);
        }
        SortingTableLift = SortingTableLift->Next;
      } while (SortingTableLift != (_ZSORTING *)0x0);
      SortingTableLift = (_ZSORTING *)0x0;
    }
    SortingTableIndexLift = SortingTableIndexLift + -1;
  }
  return;
}
