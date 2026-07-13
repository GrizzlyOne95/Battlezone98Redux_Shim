/*
 * Entry: 005157b2
 * Name: PREREQ_IsBuilding
 * Namespace: Global
 * Signature: uchar PREREQ_IsBuilding(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl PREREQ_IsBuilding(ushort param_1)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar4 = "PREREQ_IsValid(id)";
  pcVar3 = ".\\Schedule\\Prereq.c";
  iVar2 = 0x499;
  bVar1 = PREREQ_IsValid(param_1);
  Debug_Assert((uint)bVar1,iVar2,pcVar3,pcVar4);
  return PREREQ_table[param_1].type == '\x01';
}
