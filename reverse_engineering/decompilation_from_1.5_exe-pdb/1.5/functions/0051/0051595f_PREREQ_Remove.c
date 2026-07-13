/*
 * Entry: 0051595f
 * Name: PREREQ_Remove
 * Namespace: Global
 * Signature: void PREREQ_Remove(ushort param_1, char param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PREREQ_Remove(ushort param_1,char param_2)

{
  uint uVar1;
  bool bVar2;
  tagBUILDINGTYPE *ptVar3;
  
  bVar2 = false;
  if (PREREQ_online != '\0') {
    uVar1 = (uint)param_1;
    if (PREREQ_table[uVar1].type == '\x01') {
      ptVar3 = PREREQ_BuildingTypePtr(param_1);
      ptVar3 = ptVar3->upgradeof;
      if (ptVar3 != (tagBUILDINGTYPE *)0x0) {
        do {
          PREREQ_table[ptVar3->prereqtype].howmany[param_2] =
               PREREQ_table[ptVar3->prereqtype].howmany[param_2] + -1;
          if (PREREQ_table[ptVar3->prereqtype].howmany[param_2] == 0) {
            bVar2 = true;
          }
          ptVar3 = ptVar3->upgradeof;
        } while (ptVar3 != (tagBUILDINGTYPE *)0x0);
      }
    }
    PREREQ_table[uVar1].howmany[param_2] = PREREQ_table[uVar1].howmany[param_2] + -1;
    if (PREREQ_table[uVar1].howmany[param_2] == 0) {
      bVar2 = true;
    }
    if (bVar2) {
      PREREQ_Update(param_2);
    }
  }
  return;
}
