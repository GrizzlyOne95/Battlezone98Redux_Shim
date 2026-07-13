/*
 * Entry: 0051561e
 * Name: PREREQ_GetRequirements
 * Namespace: Global
 * Signature: void PREREQ_GetRequirements(ushort param_1, char param_2, char * * param_3, int * param_4, int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
PREREQ_GetRequirements(ushort param_1,char param_2,char **param_3,int *param_4,int *param_5)

{
  char cVar1;
  int *piVar2;
  ushort uVar3;
  ushort *puVar4;
  char *pcVar5;
  char *pcVar6;
  ushort *local_8;
  
  piVar2 = param_4;
  *param_4 = 0;
  *param_5 = 0;
  param_4 = (int *)0x0;
  puVar4 = PREREQ_GetAllPrereqs(param_1);
  local_8 = PREREQ_GetMakers(param_1);
  for (; *puVar4 != 0; puVar4 = puVar4 + 1) {
    uVar3 = PREREQ_GetEquivalent(*puVar4,param_2);
    if ((uVar3 != 0) && (PREREQ_table[uVar3].howmany[param_2] == 0)) {
      pcVar5 = PREREQ_MapPrereqIdtoName(uVar3);
      pcVar6 = param_3[(uint)param_4 & 0xffff];
      param_4 = (int *)((int)param_4 + 1);
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        *pcVar6 = cVar1;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      *piVar2 = *piVar2 + 1;
    }
  }
  for (; *local_8 != 0; local_8 = local_8 + 1) {
    uVar3 = PREREQ_GetEquivalent(*local_8,param_2);
    if ((uVar3 != 0) && (PREREQ_table[uVar3].howmany[param_2] == 0)) {
      pcVar5 = PREREQ_MapPrereqIdtoName(uVar3);
      pcVar6 = param_3[(uint)param_4 & 0xffff];
      param_4 = (int *)((int)param_4 + 1);
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        *pcVar6 = cVar1;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      *param_5 = *param_5 + 1;
    }
  }
  return;
}
