/*
 * Entry: 00405721
 * Name: BlockedCellInit
 * Namespace: Global
 * Signature: void BlockedCellInit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BlockedCellInit(void)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  char **ppcVar4;
  
  cellCount = (GridMaxZ - GridMinZ) * (GridMaxX - GridMinX);
  cellType = operator_new__(cellCount);
  iVar1 = cellCount;
  memset(cellType,0,cellCount);
  cellRegion = operator_new__(iVar1);
  uVar3 = cellCount;
  memset(cellRegion,0,cellCount);
  ppcVar4 = cellTeamRef;
  do {
    pcVar2 = operator_new__(uVar3);
    uVar3 = cellCount;
    *ppcVar4 = pcVar2;
    memset(pcVar2,0,uVar3);
    ppcVar4 = ppcVar4 + 1;
  } while ((int)ppcVar4 < 0x64d9e0);
  cellTeam = operator_new__(-(uint)((int)((ulonglong)uVar3 * 2 >> 0x20) != 0) |
                            (uint)((ulonglong)uVar3 * 2));
  iVar1 = cellCount;
  memset(cellTeam,0,cellCount * 2);
  ProcessCliffs(iVar1);
  return;
}
