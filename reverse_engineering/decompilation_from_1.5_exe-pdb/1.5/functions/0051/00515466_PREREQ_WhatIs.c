/*
 * Entry: 00515466
 * Name: PREREQ_WhatIs
 * Namespace: Global
 * Signature: ushort PREREQ_WhatIs(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort __cdecl PREREQ_WhatIs(char *param_1)

{
  char *pcVar1;
  int in_ECX;
  int iVar2;
  int iVar3;
  
  iVar2 = 1;
  if (1 < PREREQ_maxassigned) {
    iVar3 = 0x9c;
    do {
      pcVar1 = (char *)((int)PREREQ_table->howmany + iVar3 + -0x1c);
      if (*pcVar1 == '\0') {
        pcVar1 = (char *)(*(int *)(pcVar1 + 4) + 0x14);
LAB_005154a7:
        in_ECX = strncmp(param_1,pcVar1,0x51);
      }
      else if (*pcVar1 == '\x01') {
        pcVar1 = (char *)(*(int *)(pcVar1 + 4) + 0x40);
        goto LAB_005154a7;
      }
      if (in_ECX == 0) {
        return (ushort)iVar2;
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x9c;
    } while (iVar2 < PREREQ_maxassigned);
  }
  return 0;
}
