/*
 * Entry: 00515835
 * Name: PREREQ_BuildingTypePtr
 * Namespace: Global
 * Signature: tagBUILDINGTYPE * PREREQ_BuildingTypePtr(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagBUILDINGTYPE * __cdecl PREREQ_BuildingTypePtr(ushort param_1)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar4 = "PREREQ_IsBuilding (id)";
  pcVar3 = ".\\Schedule\\Prereq.c";
  iVar2 = 0x4c4;
  bVar1 = PREREQ_IsBuilding(param_1);
  Debug_Assert((uint)bVar1,iVar2,pcVar3,pcVar4);
  return PREREQ_table[param_1].data;
}
