/*
 * Entry: 00515556
 * Name: PREREQ_Update
 * Namespace: Global
 * Signature: void PREREQ_Update(char param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PREREQ_Update(char param_1)

{
  uchar uVar1;
  int iVar2;
  ushort *puVar3;
  PREREQ_struct *pPVar4;
  int iVar5;
  int local_4;
  
  if ((PREREQ_online != '\0') && (local_4 = 1, 1 < PREREQ_maxassigned)) {
    iVar2 = 0x9c;
    pPVar4 = PREREQ_table;
    iVar5 = (int)param_1;
    do {
      pPVar4[1].canmake[iVar5] = '\0';
      PREREQ_table[1].haveprereqs[iVar5] = '\0';
      pPVar4 = PREREQ_table;
      for (puVar3 = *(ushort **)((int)PREREQ_table->howmany + iVar2 + -0x10); *puVar3 != 0;
          puVar3 = puVar3 + 1) {
        uVar1 = PREREQ_HaveEquivalent(*puVar3,param_1);
        if (uVar1 == '\0') goto LAB_005155fb;
      }
      pPVar4[1].haveprereqs[iVar5] = '\x01';
      pPVar4 = PREREQ_table;
      for (puVar3 = *(ushort **)((int)PREREQ_table->howmany + iVar2 + -8); *puVar3 != 0;
          puVar3 = puVar3 + 1) {
        uVar1 = PREREQ_HaveEquivalent(*puVar3,param_1);
        if (uVar1 != '\0') {
          pPVar4[1].canmake[iVar5] = '\x01';
          pPVar4 = PREREQ_table;
          break;
        }
      }
LAB_005155fb:
      local_4 = local_4 + 1;
      iVar2 = iVar2 + 0x9c;
      iVar5 = iVar5 + 0x9c;
    } while (local_4 < PREREQ_maxassigned);
  }
  return;
}
