/*
 * Entry: 0051f3c3
 * Name: TerrainSaveName
 * Namespace: Global
 * Signature: void TerrainSaveName(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TerrainSaveName(char *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar4 = (int)missionName - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[iVar4] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  pcVar3 = strrchr(missionName,0x2e);
  if (pcVar3 != (char *)0x0) {
    *pcVar3 = '\0';
  }
  puVar2 = (undefined4 *)0xca6cbf;
  do {
    puVar5 = puVar2;
    puVar2 = (undefined4 *)((int)puVar5 + 1);
  } while (*(char *)((int)puVar5 + 1) != '\0');
  *(undefined4 *)((int)puVar5 + 1) = 0x4e52542e;
  *(undefined1 *)((int)puVar5 + 5) = 0;
  return;
}
