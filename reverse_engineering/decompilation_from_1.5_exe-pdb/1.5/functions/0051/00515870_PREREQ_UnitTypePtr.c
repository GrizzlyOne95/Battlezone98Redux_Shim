/*
 * Entry: 00515870
 * Name: PREREQ_UnitTypePtr
 * Namespace: Global
 * Signature: tagUNITTYPE * PREREQ_UnitTypePtr(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagUNITTYPE * __cdecl PREREQ_UnitTypePtr(ushort param_1)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar4 = "PREREQ_IsUnit (id)";
  pcVar3 = ".\\Schedule\\Prereq.c";
  iVar2 = 0x4d2;
  bVar1 = PREREQ_IsUnit(param_1);
  Debug_Assert((uint)bVar1,iVar2,pcVar3,pcVar4);
  return PREREQ_table[param_1].data;
}
